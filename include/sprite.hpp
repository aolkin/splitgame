#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "textures.hpp"

class Sprite : public sf::Drawable {
private:
  sf::Vector2i texOffset;
  SharedTexture sharedTex;
 protected:
  sf::Sprite sprite;
  bool setSheetIndex (int x, int y);
  bool setSheetIndex (sf::Vector2i index=sf::Vector2i());
 public:
  Sprite (float width, float height, bool center=true);
  /** Gets offset and Texture pointer from a TexInfo object */
  void useTexInfo(const TexInfo& texinfo);
  /** Gets offset and Texture pointer from a TexInfo object.
   * The appropriate TexInfo is retrieved from the TextureCache. */
  void useCachedTexture(const std::string& name);
  virtual bool isVisible() const { return true; };
  virtual void draw (sf::RenderTarget&, sf::RenderStates) const;

  /** Forwards method call by default. */
  virtual const sf::Vector2f& getPosition() const;
  /** Forwards method call by default. */
  virtual void setPosition(float x, float y) {
    setPosition(sf::Vector2f(x, y));
  };
  /** Forwards method call by default. */
  virtual void setPosition(const sf::Vector2f& pos);
  
  const float width, height;
  const bool centered;
};

#endif
