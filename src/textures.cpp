
#include "textures.hpp"
#include "player.hpp"

const std::string ART_DIR = "art/";

namespace TextureMapping {
  enum Textures {
    DialogueBox, DialoguePlayer
  };
  const std::unordered_map<std::string, Textures> map ({
      {"dialoguebox", DialogueBox},
      {"dialogueplayer", DialoguePlayer}
    });
}

TextureCache& TextureCache::singleton() {
  static TextureCache c;
  return c;
}

std::shared_ptr<sf::Texture> TextureCache::getTexture(std::string fn) {
  if (cache[fn].expired()) {
    #ifdef DEBUG_BUILD
    std::cout << "Texture " << fn << " expired, loading..." << std::endl;
    #endif
    
    std::shared_ptr<sf::Texture> sp = std::make_shared<sf::Texture>();
    if (!sp->loadFromFile(ART_DIR + fn)) {
      throw "Failed to load texture!";
    };
    cache[fn] = sp;
    return sp;
  } else {
    return cache[fn].lock();
  }
}

const TexInfo TextureCache::get(std::string name) {
  using namespace TextureMapping;
  switch (map.at(name)) {
  case DialogueBox:
    return TexInfo(getTexture("dialogue.png"), 0, 0);
  case DialoguePlayer:
    return TexInfo(getTexture("dialogue.png"), 294, 0);
  default:
    throw "Unknown Texture requested!";
  };
}
