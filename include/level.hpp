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

struct TickResult {
  enum ResultType { None, NewLevel };
  ResultType type;
  union {
    NewLevelStruct level;
  };
  TickResult () : type(None) { };
  TickResult (NewLevelStruct l) : type(NewLevel), level(l) { };
};

class Level : public sf::Drawable {
  Player& player;
  InputMode mode;
  struct {
    sf::Sprite sprite;
    sf::Texture texture;
    float width, height;
  } room;
  sf::View viewport;
  std::vector<Entity*> entities;
  std::vector<sf::FloatRect> bounds;
  bool withinBoundaries (const sf::FloatRect&) const;
  bool noCollisions (const sf::FloatRect&) const;
public:
  Level (Player&, sf::Image&);
  ~Level ();
  TickResult tick ();
  void handleInput (const Input::Event&);
  void draw (sf::RenderTarget&, sf::RenderStates) const;
  static Level load(std::istream&, Player&, int, const EntityFactory&);
};
  
#endif
