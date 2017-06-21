
#include "textures.hpp"

const std::string ART_DIR = "art/";

void Texture::initialize(std::string fn, sf::Vector2i i) {
  isInitialized = true;
  index = i;
  if (!texture->loadFromFile(ART_DIR + fn)) {
    throw "Failed to load texture for cache.";
  };
}

TextureCache& TextureCache::singleton() {
  static TextureCache c;
  return c;
}

const Texture& TextureCache::getTexture(std::string name) const {
  const Texture& t = cache.at(name);
  if (!t.isInitialized) {
    throw "Tried to retrieve unitialized texture!";
  }
  return t;
}

void TextureCache::initialize(Mode m) {
  if (cache.size() < 1) {
    Texture& t = cache["dialogue_box"];
    t.initialize("dialogueboxes.png", sf::Vector2i());
  }
  if (cache.size() < 1 || m != mode) {
    
  }
}
