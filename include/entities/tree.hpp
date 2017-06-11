#ifndef TREE_H
#define TREE_H

#include "entity.hpp"

namespace Entities {

  class Tree : public Entity {
  public:
    Tree (int zz) : Entity(zz) { };
    static Entity* makeNew(const std::vector<int>) {
      return new Tree(-1);
    }
  };
  
}
#endif
