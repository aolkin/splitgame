
#include <iostream>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "input.hpp"
#include "level.hpp"
#include "player.hpp"

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

  bool paused = false;
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (event.type == sf::Event::LostFocus)
	    paused = true;
	  if (event.type == sf::Event::GainedFocus)
	    paused = false;
	  active.handleInput(Input::getInput(event, keymap));
	}

      sf::Time delta = clock.restart();
      // FSM

      if (!paused) {
	active.tick();
	//player.update()
	
	window.clear(sf::Color::Black);
	
	window.draw(active);
	
	window.display();
      }
    }
  
  return 0;
}
