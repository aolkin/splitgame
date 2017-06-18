#ifndef PBHELP_HPP
#define PBHELP_HPP

#include <SFML/Graphics.hpp>
#include "pb/global.pb.h"

sf::Vector2f pbToSFVector(const pb::Vector2f &v) {
  return sf::Vector2f(v.x(), v.y());
};

sf::FloatRect pbToSFRect(const pb::FloatRect &r) {
  return sf::FloatRect(pbToSFVector(r.pos()), pbToSFVector(r.size()));
};

#endif
