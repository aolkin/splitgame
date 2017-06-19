#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "global.hpp"

namespace Textures {

  struct Texture {
    std::shared_ptr<sf::Texture> texture;
    sf::Vector2i index;
    bool isInitialized;
    Texture () : isInitialized(false) { };
  };
  
  Texture * getEntity(std::string);

}

#endif
