#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite : public sf::Drawable {
 private:
  sf::Texture texture;
  sf::Sprite sfspr;
 protected:
  int width, height, x, y, z;
  Sprite (int w, int h) : width(w), height(h) { };
  void updateTexture (const sf::Texture&);
  bool setSheetIndex (int, int);
 public:
  virtual void tick() =0;
  void draw (sf::RenderTarget&, sf::RenderStates) const;
  int getZ() { return z; };
};

#endif
