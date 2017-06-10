
#include <SFML/Graphics.hpp>

#include "global.hpp"
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

  // Initialization

  EntityFactory entity_factory;
  
  Player player;
  Level active (0, player, entity_factory);

  sf::Clock clock;
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  // If keyboard events, do movement stuff
	}

      sf::Time delta = clock.restart();
      // FSM

      active.tick();
      //player.update()
      
      window.clear(sf::Color::Black);
      
      window.draw(active);
      
      window.display();
    }
  
  return 0;
}
