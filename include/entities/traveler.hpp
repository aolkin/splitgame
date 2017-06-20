#ifndef TRAVELER_ENTITY_HPP
#define TRAVELER_ENTITY_HPP

#include "entity.hpp"

namespace Entities {

  /**
   * # Floats: x, y, width, height, new level id, level start index
   */
  class Traveler : public Entity {
  private:
    NewLevel nl;
  public:
    Traveler (float, float, float, float, NewLevel);
    static Entity* makeNew(const std::vector<float>&,
			   const std::vector<std::string>&);
    EntityAction oneTick(const sf::FloatRect&);
  };
  
}

#endif
