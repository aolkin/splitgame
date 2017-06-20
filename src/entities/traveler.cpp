
#include "entities/traveler.hpp"

namespace Entities {

  Traveler::Traveler (float w, float h, float x, float y, NewLevel n) :
    Entity(width, height, -1, Entity::ActionRect), nl(n) {
    setPosition(x, y);
    addDefaultBoundary();
  };
  
  Entity* Traveler::makeNew(const std::vector<float>& fargs,
				  const std::vector<std::string>& sargs) {
    return new Traveler(fargs[2], fargs[3], fargs[0], fargs[1],
			NewLevel((int)fargs[4], (int)fargs[5]));
  };

  EntityAction Traveler::oneTick(const sf::FloatRect& player) {
    if (hasCollided(player)) {
      return EntityAction(nl);
    } else {
      return EntityAction();
    }
  };
  
}
