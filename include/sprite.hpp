#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite : public sf::Sprite {
 protected:
  bool setSheetIndex (int x, int y);
  bool setSheetIndex (sf::Vector2i);
 public:
  Sprite (float, float, bool=true);
  virtual bool isVisible() const { return true; };
  void drawOn (sf::RenderTarget&, sf::RenderStates) const;
  const float width, height;
};

#endif
