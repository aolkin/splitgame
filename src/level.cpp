
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "global.hpp"
#include "entity_factory.hpp"
#include <algorithm>

Level::Level (int i, Player& p, EntityFactory& factory) :
  id(i), player(p), mode(InputMode::Player) {

  viewport.setSize(global::width, global::height);
  viewport.setViewport(sf::FloatRect(0, 0, 1, 1));

  entities.push_back(factory.make("Tree",{}));
};

Level::~Level () {
  for (Entity* s : entities) {
    delete s;
  }
}

void Level::handleInput (const Input::Event& input) {
  if (mode == InputMode::None || input.type == Input::None)
    return;
  if (mode == InputMode::Player) {
    float modifier = input.release ? -1.f : 1.f;
    switch (input.type)
      {
      case Input::Left:
	player.changeVelocity(sf::Vector2f(-1, 0) * modifier);
	break;
      case Input::Right:
	player.changeVelocity(sf::Vector2f(1, 0) * modifier);
	break;
      case Input::Down:
	player.changeVelocity(sf::Vector2f(0, 1) * modifier);
	break;
      case Input::Up:
	player.changeVelocity(sf::Vector2f(0, -1) * modifier);
	break;
      case Input::Okay:
	// Attempt to Interact
	break;
      default:
	break;
      }
  }
}
  
void Level::tick () {
  room.tick();
  for (Entity* s : entities) {
    std::vector<EntityAction> actions = s->doTick();
    for (EntityAction a : actions) {
      switch (a.type)
	{
	case ActionType::RestrictInput :
	  mode = a.inputMode;
	  break;
	case ActionType::MovePlayer:
	  break;
	default:
	  break;
	}
    }
  }

  sf::Vector2f newpos = player.move(false);
  if (true) {
    player.move(true);
  }
  
  player.tick();
  auto pos = player.getPosition();
  pos.x = std::max(pos.x, global::width / 2);
  pos.x = std::min(pos.x, room.width - global::width / 2);
  pos.y = std::max(pos.y, global::height / 2);
  pos.y = std::min(pos.y, room.height - global::height / 2);
  viewport.setCenter(pos);
};

#include <iostream>
void Level::draw (sf::RenderTarget& target,
		  sf::RenderStates states) const {
  target.setView(viewport);
  target.draw(room);
  int lastz = -1;
  for (Entity* s : entities) {
    if (lastz < 0 && s->z > 0) {
      target.draw(player);
    }
    lastz = s->z;
    target.draw(*s);
  }
  if (lastz < 0) {
    target.draw(player);
  }
};
