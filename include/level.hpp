#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "input.hpp"
#include "sprite.hpp"
#include "entity.hpp"
#include "room.hpp"
#include "player.hpp"
#include "entity_factory.hpp"

class Level : public sf::Drawable {
  int id;
  Player player;
  Room room;
  bool playerIsVisible;
  InputMode mode;
  sf::View viewport;
  std::vector<Entity*> entities;
  std::vector<sf::FloatRect> bounds;
  bool checkBoundaries (sf::Vector2f);
public:
  Level (int, Player&, EntityFactory&);
  ~Level ();
  void tick ();
  int getID () { return id; };
  void handleInput (const Input::Event&);
  void draw (sf::RenderTarget&, sf::RenderStates) const;
};
  
#endif
