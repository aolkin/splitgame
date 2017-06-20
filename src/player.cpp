
#include "player.hpp"

const BoolVector BoolVector::X(true, false);
const BoolVector BoolVector::Y(false, true);
const BoolVector BoolVector::TRUE(true);
const BoolVector BoolVector::FALSE(false);

Player::Player () : Sprite(22, 60, true), visible(true) {
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

void Player::changeVelocity(const sf::Vector2f& v) {
  if (v.x != velocity.x || v.y != velocity.y) {
    velocity += v;
    if (velocity.x < 0)
      direction = Facing::Left;
    else if (velocity.x > 0)
      direction = Facing::Right;
    if (velocity.y < 0)
      direction = Facing::Up;
    else if (velocity.y > 0)
      direction = Facing::Down;
  }
}

sf::Vector2f Player::getMove (const BoolVector& v, bool atFeet) const {
  sf::Vector2f tv(velocity.x * v.x, velocity.y * v.y);
  sf::Vector2f newpos = getPosition() + (tv * 2.f);
  if (atFeet) {
    newpos.y += height / 2;
  }
  return newpos;
}

void Player::move(const BoolVector& v) {
  setPosition(getMove(v));
}

sf::FloatRect Player::getBounds (const BoolVector& v) const {
  sf::Vector2f pos = getMove(v, true);
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
  if (velocity == sf::Vector2f()) {
    walkCount = 0;
  } else {
    walkCount++;
  }
  int modc;
  switch ((walkCount / 6) % 4) {
  case 1:
    modc = 4;
    break;
  case 3:
    modc = 8;
    break;
  default:
    modc = 0;
    break;
  }
  updateTexture((int)direction + modc);
}

void Player::drawOn (sf::RenderTarget& target, sf::RenderStates states) const {
  Sprite::drawOn(target, states);
  #ifdef DEBUG_BUILD
  if (Debug::mode & 4) {
    Debug::drawRect(getBounds(BoolVector::FALSE), sf::Color::Green,
		    target, states);
    Debug::drawRect(sf::FloatRect(getPosition(), sf::Vector2f()),
		    sf::Color::Green, target, states, -1);
  }
  #endif
}

Player player;
