#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"
#include "global.hpp"

enum class Facing { Down = 0, Up = 1, Left = 2, Right = 3 };

struct BoolVector {
  bool x, y;
  BoolVector (bool def=true) : x(def), y(def) { };
  BoolVector (bool ix, bool iy) : x(ix), y(iy) { };
  static const BoolVector X;
  static const BoolVector Y;
  static const BoolVector TRUE;
  static const BoolVector FALSE;
  operator bool() const { return x && y; };
};

class Player : public Sprite {
private:
  sf::Vector2f velocity;
  Mode mode;
  bool visible;
  int walkCount;
  Facing direction;
  sf::Texture usTexture;
  Player ();
  void updateTexture(int);
public:;
  void tick ();
  sf::Vector2f getVelocity () const { return velocity; };
  bool isVisible() const { return visible; };
  void setVisibility(bool);
  void setMode (Mode);
  void changeVelocity (const sf::Vector2f&);
  sf::Vector2f getMove (const BoolVector& =BoolVector::TRUE, bool=false) const;
  void move(const BoolVector& =BoolVector::TRUE);
  sf::FloatRect getBounds (const BoolVector&) const;
  void drawOn(sf::RenderTarget& target, sf::RenderStates states) const;

  static Player& singleton();
};

#endif
