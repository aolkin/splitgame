
#include <iostream>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "input.hpp"
#include "level.hpp"
#include "player.hpp"

#include "extra/movie.hpp"

#include "entity_factory.hpp"

namespace global {
  const std::string name = "SPLIT";
  const std::string splashfn = "split.mp4";
}

int main(int argc, char *argv[])
{
  using namespace global;

  sf::RenderWindow window;
  if (argc > 1)
    window.create(sf::VideoMode::getFullscreenModes()[0], name,
		  sf::Style::Fullscreen);
  else
    window.create(sf::VideoMode(width * 2, height * 2), name,
		  sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);

  sf::View defaultView = window.getDefaultView();
  
  // Initialization  

  Input::KeyMap keymap = Input::buildKeymap ();
  
  EntityFactory entity_factory;
  
  Player player;
  Level active (0, player, entity_factory);

  sf::Clock clock;

  int paused = 1;

  bool splash_playing = true;
  paused++;
  Movie splash (window);
  splash.start(global::splashfn);
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (event.type == sf::Event::LostFocus)
	    paused++;
	  if (event.type == sf::Event::GainedFocus)
	    paused--;
	  if (event.type == sf::Event::KeyPressed) {
	    if (event.key.code == sf::Keyboard::Escape) {
	      if (splash_playing) {
		splash.stop();
	      }
	    }
	  }
	  active.handleInput(Input::getInput(event, keymap));
	}

      //sf::Time delta = clock.restart();
      // FSM

      window.setView(defaultView);

      if (splash_playing) {
	splash.update();
	if (splash.done()) {
	  splash_playing = false;
	  paused--;
	} else {
	  window.draw(splash);
	}
      }
      
      if (paused == 0) {
	window.clear(sf::Color::Black);
	active.tick();
	window.draw(active);
      }
      
      window.display();
    }
  
  return 0;
}
