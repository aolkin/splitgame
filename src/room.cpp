
#include "room.hpp"

#include <iostream>

Room::Room () : Sprite(480, 270, false) {
  if (!texture.loadFromFile("art/sample.png")) {
    throw "Failed to load texture.";
  };
  setTexture(texture);
}

void Room::tick () { }
