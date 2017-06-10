#ifndef TREE_H
#define TREE_H

#include "entity.hpp"

namespace Entities {

  class Tree : public Entity {
  public:
    Tree () {};
    static Entity* makeNew(const std::vector<int>) {
      return new Tree();
    }
  };
  
}
#endif
