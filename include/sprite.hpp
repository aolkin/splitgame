#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "textures.hpp"

class Sprite : public sf::Sprite {
private:
  sf::Vector2i texOffset;
 protected:
  bool setSheetIndex (int x, int y);
  bool setSheetIndex (sf::Vector2i index=sf::Vector2i());
 public:
  Sprite (float width, float height, bool center=true);
  /** Gets offset and Texture pointer from a TexInfo object */
  void useTexInfo(TexInfo texinfo);
  virtual bool isVisible() const { return true; };
  virtual void drawOn (sf::RenderTarget&, sf::RenderStates) const;
  const float width, height;
  const bool centered;
};

#endif
