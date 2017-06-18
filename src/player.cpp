
#include "player.hpp"

Player::Player () : Sprite(22, 60), visible(true) {
  //setOrigin(11, 60);
  if (!usTexture.loadFromFile("art/player.png")) {
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

sf::Vector2f Player::move (bool doMove, BoolVector v) {
  sf::Vector2f tv(velocity.x * v.x, velocity.y * v.y);
  sf::Vector2f newpos = getPosition() + (tv * 2.f);
  if (doMove) {
    setPosition(newpos);
  }
  newpos.y += height / 2;
  return newpos;
}

sf::FloatRect Player::getBounds (BoolVector v) {
  sf::Vector2f pos = move(false, v);
  return sf::FloatRect(pos.x - width / 2,
		   pos.y - 10,
		   width, 10);
}

void Player::setVisibility(bool v) {
  visible = v;
}

void Player::updateTexture (int index) {
  setSheetIndex(index, (int)mode);
}

#include <iostream>
void Player::tick () {
  updateTexture((int)direction);
  //std::cout << getPosition().x << " " << getPosition().y << std::endl;
}
