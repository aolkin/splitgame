
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "pb/level.pb.h"
#include "extra/pbhelp.hpp"
#include <algorithm>

const std::string ROOM_ART = "art/room/";

Level Level::load(std::istream &stream, Player& p, int start,
		  const EntityFactory& factory) {
  pb::Level pbl;
  if (!pbl.ParseFromIstream(&stream)) {
    throw "Failed to parse level!";
  }

  sf::Image roomImage;
  if (!roomImage.loadFromFile(ROOM_ART + pbl.texture())) {
    throw "Failed to load room image.";
  };
  Level l(p, roomImage);

  for (int i = 0; i < pbl.bounds_size(); i++) {
    l.bounds.push_back(pbToSFRect(pbl.bounds(i)));
  }

  l.player.setVisibility(pbl.playervisibility());
  l.mode = (InputMode)pbl.inputmode();

  l.player.setPosition(pbToSFVector(pbl.starts().at(start)));

  for (int i = 0; i < pbl.entities_size(); i++) {
    pb::Entity e = pbl.entities(i);
    std::vector<float> fp;
    std::vector<std::string> sp;
    for (int j = 0; j < e.nargs_size(); j++) {
      fp.push_back(e.nargs(j));
    }
    for (int j = 0; j < e.sargs_size(); j++) {
      sp.push_back(e.sargs(i));
    }
    l.entities.push_back(factory.make(e.name(), fp, sp));
  }
  
  return l;
};

Level::Level (Player& p, sf::Image& roomImage) : player(p),
						 mode(InputMode::None) {
  sf::Vector2u roomDims = roomImage.getSize();
  room.width = (float)roomDims.x;
  room.height = (float)roomDims.y;
  if (!room.texture.loadFromImage(roomImage)) {
    throw "Failed to load room texture.";
  };
  room.sprite.setTexture(room.texture);
  
  viewport.setSize(global::width, global::height);
  viewport.setViewport(sf::FloatRect(0, 0, 1, 1));
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

void Level::draw (sf::RenderTarget& target,
		  sf::RenderStates states) const {
  target.setView(viewport);
  target.draw(room.sprite, states);
  int lastz = -1;
  for (Entity* s : entities) {
    if (lastz < 0 && s->z > 0) {
      player.drawOn(target, states);
    }
    lastz = s->z;
    s->drawOn(target, states);
  }
  if (lastz < 0) {
    player.drawOn(target, states);
  }
};
