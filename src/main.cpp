
#include <iostream>
#include <fstream>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "input.hpp"
#include "level.hpp"
#include "player.hpp"

#include "extra/movie.hpp"

#include "entity.hpp"

namespace global {
  const std::string name = "SPLIT";
  const std::string splashfn = "split.mp4";
  const sf::Time delta = sf::seconds(.03333);
}

#ifdef DEBUG_BUILD
namespace Debug {
  int mode = 0;
  
  void drawRect(const sf::FloatRect& r, const sf::Color& color,
		sf::RenderTarget& target, sf::RenderStates states) {
    sf::RectangleShape rect(sf::Vector2f(r.width - 2, r.height - 2));
    rect.setPosition(r.left + 1, r.top + 1);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(color);
    rect.setFillColor(sf::Color::Transparent);
    target.draw(rect, states);
  };
}
#endif

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
  std::ifstream file("rooms/001.dat",
		     std::ios::in | std::ios::binary);
  Level active = Level::load(file, player, 0, entity_factory);
  file.close();

  sf::Clock clock;
  sf::Time delta;

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

      delta += clock.restart();

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
	if (delta > global::delta) {
	  delta -= global::delta;
	  TickResult result = active.tick();
	}
	window.draw(active);
      }
      
      window.display();
    }
  
  return 0;
}
