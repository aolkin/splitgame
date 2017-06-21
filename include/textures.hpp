#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <unordered_map>
#include "player.hpp"

class Texture;

class TextureCache {
  std::unordered_map<std::string, Texture> cache;
  Mode mode;
public:
  void initialize(Mode m);
  const Texture& getTexture(std::string) const;
  static TextureCache& singleton();
};

class Texture {
  friend class TextureCache;
private:
  bool isInitialized;
  void initialize(std::string, sf::Vector2i);
public:
  std::shared_ptr<sf::Texture> texture;
  sf::Vector2i index;
  Texture () : isInitialized(false) { };
};

#endif
