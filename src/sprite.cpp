
#include <SFML/Graphics.hpp>

#include "sprite.hpp"

Sprite::Sprite (float w, float h): width(w), height(h) {
  setOrigin(w / 2, h / 2); // Center origin
};

void Sprite::updateTexture (const sf::Texture& t) {
  setTexture(t);
  setSheetIndex(0, 0);
};

bool Sprite::setSheetIndex (int x, int y) {
  // TODO: error-checking
  setTextureRect(sf::IntRect(x * width, y * height, width, height));
  return true;
};

