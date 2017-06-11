#ifndef ROOM_H
#define ROOM_H

#include "sprite.hpp"

class Room : public Sprite {
private:
  sf::Texture texture;
public:
  void tick ();
  Room ();
};

#endif
