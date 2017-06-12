
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "global.hpp"
#include "entity_factory.hpp"
#include <algorithm>

Level::Level (int i, Player& p, EntityFactory& factory) :
  id(i), player(p), mode(InputMode::Player) {

  playerIsVisible = true;
  room.width = 480;
  room.height = 270;
  
  if (!room.texture.loadFromFile("art/sample.png")) {
    throw "Failed to load texture.";
  };
  room.sprite.setTexture(room.texture);
  
  viewport.setSize(global::width, global::height);
  viewport.setViewport(sf::FloatRect(0, 0, 1, 1));

  bounds.push_back(sf::FloatRect(0, 0, room.width, room.height));
  
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

bool Level::checkBoundaries (sf::Vector2f pos) {
  bool okay = false;
  for (sf::FloatRect r : bounds) {
    okay = okay || r.contains(pos);
  }
  return okay;
};

void Level::tick () {
  sf::Vector2f newpos = player.move(false);
  newpos.y += player.height / 2;
  bool okayToMove = checkBoundaries(newpos);
  sf::FloatRect newrect = player.getBounds(okayToMove);
  
  for (Entity* s : entities) {
    std::vector<EntityAction> actions = s->tick(newrect);
    for (EntityAction a : actions) {
      switch (a.type)
	{
	case ActionType::CancelMove:
	  okayToMove = false;
	  newrect = player.getBounds(false);
	  break;
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
  
  player.move(okayToMove);
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
  target.draw(room.sprite);
  int lastz = -1;
  for (Entity* s : entities) {
    if (lastz < 0 && s->z > 0 && playerIsVisible) {
      target.draw(player);
    }
    lastz = s->z;
    target.draw(*s);
  }
  if (lastz < 0 && playerIsVisible) {
    target.draw(player);
  }
};
