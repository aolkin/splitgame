#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"

enum class Mode { Unsplit = 0, Creative = 2, Logical = 3 };
enum class Facing { Down = 0, Up = 1, Left = 2, Right = 3 };

class Player : public Sprite {
private:
  sf::Vector2f velocity;
  Mode mode;
  Facing direction;
  sf::Texture usTexture;
  void updateTexture(int);
public:
  void tick ();
  sf::Vector2f getVelocity () const { return velocity; };
  void setMode (Mode);
  void changeVelocity (sf::Vector2f);
  sf::Vector2f move (bool);
  Player ();
};

#endif
