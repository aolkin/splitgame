#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite : public sf::Sprite {
 protected:
  Sprite (float, float, bool=true);
  bool setSheetIndex (int x, int y);
  bool setSheetIndex (sf::Vector2i);
 public:
  const float width, height;
  sf::Vector2f getCenter () const;
};

#endif
