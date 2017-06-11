
#include "player.hpp"

Player::Player () : Sprite(14, 40) {
  if (!usTexture.loadFromFile("art/playersprite.png")) {
    throw "Failed to load texture.";
  };
  setMode(Mode::Unsplit);
};

void Player::setMode (Mode nm) {
  mode = nm;
  switch (mode)
    {
    case Mode::Creative:
      break;
    case Mode::Logical:
      break;
    default:
      setTexture(usTexture);
      break;
    }
}

void Player::changeVelocity(sf::Vector2f v) {
  if (v.x != velocity.x || v.y != velocity.y) {
    velocity += v;
  }
  if (velocity.x < 0)
    direction = Facing::Left;
  else if (velocity.x > 0)
    direction = Facing::Right;
  if (velocity.y < 0)
    direction = Facing::Up;
  else if (velocity.y > 0)
    direction = Facing::Down;
}

sf::Vector2f Player::move (bool doMove) {
  sf::Vector2f newpos = getPosition() + (velocity * 2.f);
  if (doMove) {
    setPosition(newpos);
  }
  return newpos;
}

void Player::updateTexture (int index) {
  setSheetIndex(index, (int)mode);
}

#include <iostream>
void Player::tick () {
  updateTexture((int)direction);
  std::cout << getPosition().x << " " << getPosition().y << std::endl;
}
