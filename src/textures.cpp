
#include <unordered_map>
#include "textures.hpp"

namespace Textures {

  static std::unordered_map<std::string, Texture> entity_cache;
  
  Texture getEntity(std::string name) {
    Texture t = entity_cache[name];
    if (!t.isInitialized) {
      // Load from file
    }
    return t;
  }
  
}
