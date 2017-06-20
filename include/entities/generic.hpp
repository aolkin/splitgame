#ifndef GENERIC_ENTITY_HPP
#define GENERIC_ENTITY_HPP

#include "entity.hpp"

namespace Entities {

  /**
   * # Floats: x, y, impassable
   *
   * # Strings: texture file
   */
  class Generic : public Entity {
  private:
    bool impassable;
    sf::Texture t;
  public:
    Generic (sf::Image&, int, int, float, float, int, int=1);
    bool isPassable() const { return !impassable; };
    static Entity* makeNew(const std::vector<float>&,
			   const std::vector<std::string>&);
    void silentTick(bool);
  };
  
}

#endif
