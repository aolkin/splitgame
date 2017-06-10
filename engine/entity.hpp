#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "sprite.hpp"

class Entity : public Sprite {
protected:
  void tick () {};
public:
  // TODO: fix this
  Entity () : Sprite(0,0) {};
};

typedef Entity* (*MakerFunc)(const std::vector<int>);

#endif
