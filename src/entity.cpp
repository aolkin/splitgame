
#include "entity.hpp"

std::vector<EntityAction> Entity::tick (bool interacted,
					const sf::FloatRect& player) {
  std::vector<EntityAction> v;
  switch (tickMode) {
  case Silent:
    silentTick();
    break;
  case SilentInteract:
    silentTick(interacted);
    break;
  case SilentRect:
    silentTick(interacted, player);
    break;
  case Action:
    v.push_back(oneTick());
    break;
  case ActionInteract:
    v.push_back(oneTick(interacted));
    break;
  case ActionRect:
    v.push_back(oneTick(interacted, player));
    break;
  }
  return v;
}

void Entity::addDefaultBoundary() {
  sf::Vector2f pos = getPosition();
  if (centered) {
    pos.x -= width / 2;
    pos.y -= height / 2;
  }
  bounds.push_back(sf::FloatRect(pos, sf::Vector2f(width, height)));
}

void Entity::addInteractiveBoundary(float margin) {
  sf::Vector2f pos = getPosition();
  if (centered) {
    pos.x -= width / 2;
    pos.y -= height / 2;
  }
  pos.x -= margin;
  pos.y -= margin;
  auto size = sf::Vector2f(width + margin * 2, height + margin * 2);
  interactive_bounds.push_back(sf::FloatRect(pos, size));
}

bool Entity::hasCollided (const sf::FloatRect& player, bool interactive) {
  bool collided = false;
  for (sf::FloatRect r : (interactive ? interactive_bounds : bounds)) {
    collided = collided || r.intersects(player);
  }
  return collided;
}

void Entity::setPosition(const sf::Vector2f& pos) {
  sf::Vector2f delta = pos - getPosition();
  for (sf::FloatRect& r : bounds) {
    r.left += delta.x;
    r.top += delta.y;
  }
  for (sf::FloatRect& r : interactive_bounds) {
    r.left += delta.x;
    r.top += delta.y;
  }
  Sprite::setPosition(pos);
}

void Entity::setPosition(float x, float y) {
  setPosition(sf::Vector2f(x, y));
}

void Entity::draw (sf::RenderTarget& target, sf::RenderStates states) const {
  Sprite::draw(target, states);
  #ifdef DEBUG_BUILD
  if (Debug::mode & 2) {
    for (sf::FloatRect r : bounds) {
      Debug::drawRect(r, getDebugRectColor(), target, states);
    }
    for (sf::FloatRect r : interactive_bounds) {
      Debug::drawRect(r, sf::Color::Magenta, target, states);
    }
  }
  #endif
}

#ifdef DEBUG_BUILD
sf::Color Entity::getDebugRectColor () const {
  return isPassable() ? sf::Color::Blue : sf::Color::Yellow;
};
#endif
