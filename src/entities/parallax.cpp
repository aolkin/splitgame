
#include "entities/parallax.hpp"

namespace Entities {

  Parallax::Parallax (std::string tex, int width, int height,
		      float x, float y, int z) : Generic(tex, width, height,
							 x, y, z, 0),
						 startx(x), starty(y) {
    tickMode = Entity::SilentRect;
  };
  
  Entity* Parallax::makeNew(const std::vector<float>& fargs,
				  const std::vector<std::string>& sargs) {
    return new Parallax(sargs[0], fargs[2], fargs[3], fargs[0], fargs[1],
			fargs[4]);
  };

  void Parallax::silentTick(bool interact, const sf::FloatRect& rect) {
    float x = rect.left + rect.width / 2;
    setPosition(startx + (z * x) / 100.f, starty);
  };
  
}
