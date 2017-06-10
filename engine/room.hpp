#ifndef ROOM_H
#define ROOM_H

#include "sprite.hpp"

class Room : public Sprite {
protected:
  void tick ();
public:
  Room () : Sprite(0,0) { };
};

#endif
