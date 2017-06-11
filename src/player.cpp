
#include "player.hpp"

Player::Player () : Sprite(0,0), mode(Mode::Unsplit) { };

void Player::changeVelocity(sf::Vector2f v) {
  if (v.x != velocity.x || v.y != velocity.y) {
    velocity += v;
  }
}

sf::Vector2f Player::move (bool doMove) {
  sf::Vector2f newpos = getPosition() + (velocity * 1.f);
  if (doMove) {
    setPosition(newpos);
  }
  return newpos;
}

#include <iostream>
void Player::tick () {
  //std::cout << getPosition().x << " " << getPosition().y << std::endl;
}
