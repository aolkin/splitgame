
#include "entities/generic.hpp"

namespace Entities {

  Generic::Generic (sf::Image& teximg, int width, int height,
		    float x, float y, int z,
		    int impass) :
    Entity(width, height, z), impassable(impass) {
    setPosition(x, y);
    addDefaultBoundary();
    t.loadFromImage(teximg);
    setTexture(t);
  };
  
  Entity* Generic::makeNew(const std::vector<float>& fargs,
				  const std::vector<std::string>& sargs) {
    sf::Image image;
    image.loadFromFile(ENTITY_ART + sargs[0]);
    sf::Vector2u dims = image.getSize();
    return new Generic(image, dims.x, dims.y, fargs[0], fargs[1], -1,
		       fargs[2]);
  };
  
}
