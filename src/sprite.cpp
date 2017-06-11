
#include <SFML/Graphics.hpp>

#include "sprite.hpp"

Sprite::Sprite (float w, float h, bool center):
  width(w), height(h) {
  if (center)
    setOrigin(w / 2, h / 2); // Center origin
};

bool Sprite::setSheetIndex (sf::Vector2i index) {
  return setSheetIndex(index.x, index.y);
};

bool Sprite::setSheetIndex (int x, int y) {
  setTextureRect(sf::IntRect(x * width, y * height,
			     width, height));
  return true;
};

