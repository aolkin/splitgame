#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "input.hpp"
#include "sprite.hpp"
#include "entity.hpp"
#include "player.hpp"

class Level : public sf::Drawable {
  Player player;
  InputMode mode;
  struct {
    sf::Sprite sprite;
    sf::Texture texture;
    float width, height;
  } room;
  sf::View viewport;
  std::vector<Entity*> entities;
  std::vector<sf::FloatRect> bounds;
  bool checkBoundaries (sf::Vector2f);
public:
  Level (Player&, sf::Image&);
  ~Level ();
  void tick ();
  void handleInput (const Input::Event&);
  void draw (sf::RenderTarget&, sf::RenderStates) const;
  static Level load(std::istream&, Player&, int, const EntityFactory&);
};
  
#endif
