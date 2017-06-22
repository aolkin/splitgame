
#include <SFML/Graphics.hpp>

#include "sprite.hpp"
#include "textures.hpp"

Sprite::Sprite (float w, float h, bool center):
  width(w), height(h), centered(center) {
  if (center) {
    sprite.setOrigin(w / 2, h / 2); // Center origin
  }
};

void Sprite::useCachedTexture (const std::string& tex) {
  useTexInfo(TextureCache::singleton().get(tex));
}

void Sprite::useTexInfo (const TexInfo& info) {
  sharedTex = info.texture;
  sprite.setTexture(*sharedTex);
  texOffset = info.offset;
  setSheetIndex();
};

bool Sprite::setSheetIndex (sf::Vector2i index) {
  return setSheetIndex(index.x, index.y);
};

bool Sprite::setSheetIndex (int x, int y) {
  sprite.setTextureRect(sf::IntRect(x * width + texOffset.x,
			     y * height + texOffset.y,
			     width, height));
  return true;
};

void Sprite::draw (sf::RenderTarget& target, sf::RenderStates states) const {
  if (isVisible()) {
    target.draw(sprite, states);
  }
}

const sf::Vector2f& Sprite::getPosition() const {
  return sprite.getPosition();
}

void Sprite::setPosition(const sf::Vector2f& pos) {
  sprite.setPosition(pos);
}
