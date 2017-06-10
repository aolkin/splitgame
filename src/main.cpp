
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
}

int main()
{
  using namespace global;
  
  sf::RenderWindow window(sf::VideoMode(width, height), name,
		    sf::Style::Titlebar | sf::Style::Close);
  /*sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], name,
    sf::Style::Fullscreen);*/
  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);

  // Initialization  

  Input::KeyMap keymap = Input::buildKeymap ();
  
  EntityFactory entity_factory;
  
  Player player;
  Level active (0, player, entity_factory);

  sf::Clock clock;

  int paused = 0;

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
	  active.handleInput(Input::getInput(event, keymap));
	}

      sf::Time delta = clock.restart();
      // FSM

      window.clear(sf::Color::Black);

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
	active.tick();
	//player.update()	
	
	window.draw(active);
      }
      
      window.display();
    }
  
  return 0;
}
