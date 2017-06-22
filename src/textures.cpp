
#include "textures.hpp"
#include "player.hpp"

const std::string ART_DIR = "art/";

namespace TextureMapping {
  struct Info {
    std::string fn;
    sf::Vector2i os;
    Info (const std::string& f) : fn(f) { };
    Info (const std::string& f, int x, int y) : fn(f), os(x, y) { };
  };
    
  const std::unordered_map<std::string, Info> map ({
      {"dialoguebox", Info("dialogue.png", 0, 0)},
      {"dialogueplayer", Info("dialogue.png", 294, 0)}
    });
}

TextureCache& TextureCache::singleton() {
  static TextureCache c;
  return c;
}

SharedTexture TextureCache::getTexture(const std::string& fn) {
  if (cache[fn].expired()) {
    #ifdef DEBUG_BUILD
    std::cout << "Texture " << fn << " expired, loading..." << std::endl;
    #endif
    
    SharedTexture sp = std::make_shared<sf::Texture>();
    if (!sp->loadFromFile(ART_DIR + fn)) {
      throw "Failed to load texture!";
    };
    cache[fn] = sp;
    return sp;
  } else {
    return cache[fn].lock();
  }
}

const TexInfo TextureCache::get(const std::string& name) {
  try {
    TextureMapping::Info info = TextureMapping::map.at(name);
    return TexInfo(getTexture(info.fn), info.os);
  } catch (std::out_of_range) {
    return TexInfo(getTexture(name));
  }
}
