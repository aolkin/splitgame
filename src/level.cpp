
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "global.hpp"
#include "entity_factory.hpp"

Level::Level (int i, Player& p, EntityFactory& factory) :
  id(i), player(p), mode(InputMode::Player) {

  smallScale.setSize(global::width, global::height);
  largeScale.setSize(global::width / 2, global::height / 2);
  smallScale.setViewport(sf::FloatRect(0, 0, 1, 1));
  smallScale.setViewport(sf::FloatRect(0, 0, 1, 1));

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
	player.changeVelocity(sf::Vector2f(0, -1) * modifier);
	break;
      case Input::Up:
	player.changeVelocity(sf::Vector2f(0, 1) * modifier);
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
  largeScale.setCenter(player.getPosition());
  smallScale.setCenter(player.getPosition() * 2.f);
};

void Level::draw (sf::RenderTarget& target,
		  sf::RenderStates states) const {
  target.setView(largeScale);
  target.draw(room);
  int lastz = -1;
  for (Entity* s : entities) {
    if (lastz < 0 && s->z > 0) {
      target.setView(largeScale);
      target.draw(player);
    }
    lastz = s->z;
    if (s->isSmall())
      target.setView(smallScale);
    else
      target.setView(largeScale);
    target.draw(*s);
  }
};
