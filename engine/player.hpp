#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.hpp"

enum class Movement { None, Left, Right, Up, Down };

enum class Mode { Unsplit, Creative, Logical };

class Player : public Sprite {
private:
  Mode mode;
  Movement direction;
protected:
  void tick () {};
public:
  Player () : Sprite(0,0), mode(Mode::Unsplit), direction(Movement::None)
	       { };
  Movement getDirection () { return direction; };
  void setDirection (Movement);
  
};

#endif
