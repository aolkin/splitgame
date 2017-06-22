#ifndef GENERIC_ENTITY_HPP
#define GENERIC_ENTITY_HPP

#include "entity.hpp"

namespace Entities {

  /**
   * # Floats: x, y, width, height, impassable, z = -1
   *
   * # Strings: texture file
   */
  class Generic : public Entity {
  private:
    bool impassable;
  public:
    Generic (std::string, int, int, float, float, int, int=1);
    bool isPassable() const { return !impassable; };
    static Entity* makeNew(const std::vector<float>&,
			   const std::vector<std::string>&);
  };
  
}

#endif
