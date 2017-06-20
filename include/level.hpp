#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <memory>

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
    struct NewLevel level;
  };
  TickResult () : type(None) { };
  TickResult (struct NewLevel l) : type(NewLevel), level(l) { };
};

class Level : public sf::Drawable {
  sf::Vector2f startPosition;
  bool playerVisibility;
  Mode playerMode;
  InputMode mode;
  struct {
    sf::Sprite sprite;
    sf::Texture texture;
    float width, height;
  } room;
  sf::View viewport;
  std::vector<std::shared_ptr<Entity>> entities;
  std::unordered_set<std::shared_ptr<Entity>> queued_interactions;
  std::vector<sf::FloatRect> bounds;
  bool withinBoundaries (const sf::FloatRect&) const;
  bool noCollisions (const sf::FloatRect&) const;
public:
  Level (sf::Image&);
  void activatePlayer();
  TickResult tick ();
  void handleInput (const Input::Event&);
  void draw (sf::RenderTarget&, sf::RenderStates) const;
  static std::unique_ptr<Level> load(NewLevel);
  static std::unique_ptr<Level> load(int, int);
  static std::unique_ptr<Level> load(std::istream&, int);
  static std::unique_ptr<Level> load(const std::string&, int);
};

#endif
