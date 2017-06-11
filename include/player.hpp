#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"

enum class Mode { Unsplit, Creative, Logical };

class Player : public Sprite {
private:
  sf::Vector2f velocity;
  Mode mode;
public:
  void tick ();
  sf::Vector2f getVelocity () const { return velocity; };
  void changeVelocity (sf::Vector2f);
  sf::Vector2f move (bool);
  Player ();
};

#endif
