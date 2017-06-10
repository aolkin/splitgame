
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "entity_factory.hpp"

Level::Level (int i, Player& p, EntityFactory& factory) :
  id(i), player(p), mode(InputMode::Player) {
  entities.push_back(factory.make("Tree",{}));
};

Level::~Level () {
  for (Entity* s : entities) {
    delete s;
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
  player.tick();
};

void Level::handleInput (const Input::Event& input) {
  if (mode == InputMode::None || input.type == Input::None)
    return;
  if (mode == InputMode::Player) {
    switch (input.type)
      {
      case Input::Left:
	player.changeXV(input.release);
	break;
      case Input::Right:
	player.changeXV(!input.release);
	break;
      case Input::Down:
	player.changeYV(input.release);
	break;
      case Input::Up:
	player.changeYV(!input.release);
	break;
      case Input::Okay:
	// Attempt to Interact
	break;
      default:
	break;
      }
  }
}

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
