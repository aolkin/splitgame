#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite : public sf::Sprite {
 protected:
  float width, height;
  Sprite (float, float);
  void updateTexture (const sf::Texture&);
  bool setSheetIndex (int, int);
 public:
  int z;
  virtual void tick() =0;
  sf::Vector2f getCenter () const;
};

#endif
