
#include "player.hpp"

MovementVector::MovementVector () {
  v.push_back(0);
  v.push_back(0);
}

bool MovementVector::change(int index, bool positive) {
  if (positive && v[index] < 1) {
    v[index]++;
    return true;
  } else if (!positive && v[index] > -1) {
    v[index]--;
    return true;
  }
  return false;
}

bool MovementVector::changeXV(bool positive) {
  return change(0, positive);
}

bool MovementVector::changeYV(bool positive) {
  return change(1, positive);
}

void MovementVector::resetV () {
  v[0] = 0;
  v[1] = 0;
}

#include <iostream>
void Player::tick () {
  std::cout << getXV() << " " << getYV() << std::endl;;
}
