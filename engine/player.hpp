#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"

enum class Mode { Unsplit, Creative, Logical };

class MovementVector {
private:
  std::vector<int> v;
  bool change(int, bool);
public:
  MovementVector ();
  bool changeXV (bool);
  bool changeYV (bool);
  int getXV () { return v[0]; };
  int getYV () { return v[1]; };
  void resetV ();
};

class Player : public Sprite, public MovementVector {
private:
  Mode mode;
public:
  void tick ();
  Player () : Sprite(0,0), mode(Mode::Unsplit)
	       { };
};

#endif
