
#include "entity.hpp"

std::vector<EntityAction> Entity::tick (const sf::FloatRect& player) {
  return std::vector<EntityAction>();
}

void Entity::addDefaultBoundary() {
  sf::Vector2f pos = getPosition();
  if (centered) {
    pos.x -= width / 2;
    pos.y -= height / 2;
  }
  bounds.push_back(sf::FloatRect(pos, sf::Vector2f(width, height)));
}

bool Entity::hasCollided (const sf::FloatRect& player) {
  bool collided = false;
  for (sf::FloatRect r : bounds) {
    collided = collided || r.intersects(player);
  }
  return collided;
}

void Entity::drawOn (sf::RenderTarget& target, sf::RenderStates states) const {
  Sprite::drawOn(target, states);
  #ifdef DEBUG_BUILD
  if (Debug::mode & 2) {
    for (sf::FloatRect r : bounds) {
      Debug::drawRect(r, isPassable()?sf::Color::Blue:sf::Color::Yellow,
		      target, states);
    }
  }
  #endif
}
