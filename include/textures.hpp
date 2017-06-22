#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <unordered_map>

typedef std::shared_ptr<sf::Texture> SharedTexture;

class TextureCache;

struct TexInfo {
  SharedTexture texture;
  sf::Vector2i offset;
  friend class TextureCache;
private:
  TexInfo (const SharedTexture& t, int x, int y) :
    texture(t), offset(x, y) { };
  TexInfo (const SharedTexture& t, const sf::Vector2i& v = sf::Vector2i()) :
    texture(t), offset(v) { };
};

class TextureCache {
  std::unordered_map<std::string, std::weak_ptr<sf::Texture>> cache;
  SharedTexture getTexture(const std::string& fn);
public:
  const TexInfo get(const std::string&);
  static TextureCache& singleton();
};

#endif
