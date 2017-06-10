#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite : public sf::Drawable {
 private:
  sf::Texture texture;
  sf::Sprite sfspr;
  int tickCount, tickReq;
  
 protected:
  int width, height, x, y, z;
  Sprite (int w, int h) : width(w), height(h) { };
  void updateTexture (const sf::Texture&);
  bool setSheetIndex (int, int);
  void setTickReq(int req);
  virtual void tick () =0;
 public:
  void doTick();
  void draw (sf::RenderTarget&, sf::RenderStates) const;
  int getZ() { return z; };
};

#endif
