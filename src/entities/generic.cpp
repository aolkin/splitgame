
#include "entities/generic.hpp"

namespace Entities {

  Generic::Generic (std::string tex, int width, int height,
		    float x, float y, int z,
		    int impass) :
    Entity(width, height, z), impassable(impass) {
    setPosition(x, y);
    addDefaultBoundary();
    #ifdef DEBUG_BUILD
    if (tex.substr(tex.find_last_of('.')) == ".png") {
      useCachedTexture("entity/" + tex);
    } else {
    #endif
    useCachedTexture(tex);
    #ifdef DEBUG_BUILD
    }
    #endif
  };
  
  Entity* Generic::makeNew(const std::vector<float>& fargs,
				  const std::vector<std::string>& sargs) {
    int z = fargs.size() > 5 ? fargs[5] : -1;
    return new Generic(sargs[0], fargs[2], fargs[3], fargs[0], fargs[1], z,
		       fargs[4]);
  };
  
}
