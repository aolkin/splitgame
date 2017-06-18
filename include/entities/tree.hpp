#ifndef TREE_H
#define TREE_H

#include "entity.hpp"

namespace Entities {

  class Tree : public Entity {
  public:
    Tree (int zz) : Entity(zz) { };
    static Entity* makeNew(const std::vector<float>, const std::vector<std::string>) {
      return new Tree(-1);
    }
  };
  
}
#endif
