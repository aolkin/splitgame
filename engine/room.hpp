#ifndef ROOM_H
#define ROOM_H

#include "sprite.hpp"

class Room : public Sprite {
public:
  void tick ();
  Room () : Sprite(0,0) { };
};

#endif
