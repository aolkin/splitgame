
#include <SFML/Graphics.hpp>

#include "sprite.hpp"

Sprite::Sprite (float w, float h, bool center):
  width(w), height(h), centered(center) {
  if (center) {
    setOrigin(w / 2, h / 2); // Center origin
  }
};

void Sprite::useTexInfo (const TexInfo& info) {
  sharedTex = info.texture;
  setTexture(*sharedTex);
  texOffset = info.offset;
  setSheetIndex();
};

bool Sprite::setSheetIndex (sf::Vector2i index) {
  return setSheetIndex(index.x, index.y);
};

bool Sprite::setSheetIndex (int x, int y) {
  setTextureRect(sf::IntRect(x * width + texOffset.x,
			     y * height + texOffset.y,
			     width, height));
  return true;
};

void Sprite::drawOn (sf::RenderTarget& target, sf::RenderStates states) const {
  if (isVisible()) {
    target.draw(*this, states);
  }
}
