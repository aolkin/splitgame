
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "entity_factory.hpp"

Level::Level (int i, Player p, EntityFactory factory) : id(i), player(p) {
  entities.push_back(factory.make("Tree",{}));
};

Level::~Level () {
  for (Entity* s : entities) {
    delete s;
  }
}
  
void Level::tick () {
  room.doTick();
  for (Entity* s : entities) {
    s->doTick();
  }
  player.doTick();
};

void Level::draw (sf::RenderTarget& target,
		  sf::RenderStates states) const {
  target.draw(room);
  int lastz = -1;
  for (Entity* s : entities) {
    if (lastz < 0 && s->getZ() > 0) {
      target.draw(player);
    }
    lastz = s->getZ();
    target.draw(*s);
  }
};
