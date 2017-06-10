
#include <SFML/Graphics.hpp>

#include "sprite.hpp"

void Sprite::updateTexture (const sf::Texture& t) {
  texture = t;
  sfspr.setTexture(texture);
  setSheetIndex(0, 0);
};

bool Sprite::setSheetIndex (int x, int y) {
  // TODO: error-checking
  sfspr.setTextureRect(sf::IntRect(x * width, y * height, width, height));
  return true;
};

void Sprite::draw (sf::RenderTarget& target,
			   sf::RenderStates states) const {
  target.draw(sfspr);
};
