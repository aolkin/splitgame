#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include "sprite.hpp"
#include "player.hpp"

class Dialogue : public sf::Drawable {
private:
  Sprite npc_icon;
  Sprite npc_box;
  Sprite player_icon;
  Sprite player_box;
public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
