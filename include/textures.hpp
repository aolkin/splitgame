#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <unordered_map>

struct TexInfo {
  std::shared_ptr<sf::Texture> texture;
  sf::Vector2i offset;
  TexInfo (std::shared_ptr<sf::Texture> t, int x, int y) :
    texture(t), offset(x, y) { };
};

class TextureCache {
  std::unordered_map<std::string, std::weak_ptr<sf::Texture>> cache;
  std::shared_ptr<sf::Texture> getTexture(std::string fn);
public:
  const TexInfo get(std::string);
  static TextureCache& singleton();
};

#endif
