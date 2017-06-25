#ifndef PARALLAX_ENTITY_HPP
#define PARALLAX_ENTITY_HPP

#include "generic.hpp"

namespace Entities {

  /**
   * # Floats: x, y, width, height, z
   *
   * # Strings: texture file
   */
  class Parallax : public Generic {
  private:
    float startx, starty;
  public:
    Parallax (std::string, int, int, float, float, int);
    static Entity* makeNew(const std::vector<float>&,
			   const std::vector<std::string>&);
    void silentTick(bool, const sf::FloatRect&);
  };
  
}

#endif
