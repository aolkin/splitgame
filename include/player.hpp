#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"
#include "global.hpp"

enum class Facing { Down = 0, Up = 1, Left = 2, Right = 3 };

class Player : public Sprite {
private:
  sf::Vector2f velocity;
  Mode mode;
  bool visible;
  Facing direction;
  sf::Texture usTexture;
  void updateTexture(int);
public:
  void tick ();
  sf::Vector2f getVelocity () const { return velocity; };
  bool isVisible() const { return visible; };
  void setVisibility(bool);
  void setMode (Mode);
  void changeVelocity (sf::Vector2f);
  sf::Vector2f move (bool);
  sf::FloatRect getBounds (bool=false);
  Player ();
};

#endif
