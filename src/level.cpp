
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "pb/level.pb.h"
#include "extra/pbhelp.hpp"
#include <algorithm>

const std::string ROOM_ART = "art/room/";
const std::string ROOM_DIR = "rooms/";

std::unique_ptr<Level> Level::load(NewLevel nl) {
  return load(nl.id, nl.start);
}

std::unique_ptr<Level> Level::load(int id, int start) {
  std::string sid = std::to_string(id);
  std::string padded = std::string(3 - sid.length(), '0') + sid;
  return load(ROOM_DIR + padded + ".dat", start);
};

std::unique_ptr<Level> Level::load(const std::string& fn, int start) {
  std::ifstream file(fn, std::ios::in | std::ios::binary);
  auto l = load(file, start);
  file.close();
  return l;
};
  
std::unique_ptr<Level> Level::load(std::istream &stream, int start) {
  pb::Level pbl;
  if (!pbl.ParseFromIstream(&stream)) {
    throw "Failed to parse level!";
  }

  sf::Image roomImage;
  if (!roomImage.loadFromFile(ROOM_ART + pbl.texture())) {
    throw "Failed to load room image.";
  };
  auto l = std::make_unique<Level>(roomImage);

  for (int i = 0; i < pbl.bounds_size(); i++) {
    l->bounds.push_back(pbToSFRect(pbl.bounds(i)));
  }

  l->playerVisibility = pbl.playervisibility();
  l->playerMode = (Mode)pbl.playermode();
  l->mode = (InputMode)pbl.inputmode();
  l->startPosition = pbToSFVector(pbl.starts().at(start));

  for (int i = 0; i < pbl.entities_size(); i++) {
    pb::Entity e = pbl.entities(i);
    std::vector<float> fp;
    std::vector<std::string> sp;
    for (int j = 0; j < e.nargs_size(); j++) {
      fp.push_back(e.nargs(j));
    }
    for (int j = 0; j < e.sargs_size(); j++) {
      sp.push_back(e.sargs(j));
    }
    l->entities.push_back(entity_factory.make(e.name(), fp, sp));
  }
  
  return l;
};

Level::Level (sf::Image& roomImage) : mode(InputMode::None) {
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

void Level::activatePlayer () {
  player.setPosition(startPosition);
  player.setVisibility(playerVisibility);
  player.setMode(playerMode);
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
	for (auto s : entities) {
	  if (s->hasCollided(player.getBounds(BoolVector::FALSE), true)) {
	    queued_interactions.insert(s);
	  };
	}
	break;
      default:
	break;
      }
  }
}

bool Level::withinBoundaries (const sf::FloatRect& pbs) const {
  sf::Vector2f tl(pbs.left, pbs.top);
  sf::Vector2f tr(pbs.left + pbs.width, pbs.top);
  sf::Vector2f bl(pbs.left, pbs.top + pbs.height);
  sf::Vector2f br(pbs.left + pbs.width, pbs.top + pbs.height);
  BoolVector okaytop = BoolVector(false);
  BoolVector okaybottom = BoolVector(false);
  for (sf::FloatRect r : bounds) {
    okaytop.x = okaytop.x || r.contains(tl);
    okaytop.y = okaytop.y || r.contains(tr);
    okaybottom.x = okaybottom.x || r.contains(bl);
    okaybottom.y = okaybottom.y || r.contains(br);
    if (okaytop && okaybottom) {
      return true;
    }
  }
  return false;
};

bool Level::noCollisions(const sf::FloatRect& b) const {
  if (withinBoundaries(b)) {
    for (auto s : entities) {
      if (!s->isPassable() && s->hasCollided(b)) {
	return false;
      }
    }
    return true;
  }
  return false;
};

TickResult Level::tick () {
  TickResult res;
  BoolVector okayToMove;
  okayToMove.x = noCollisions(player.getBounds(BoolVector::X));
  okayToMove.y = noCollisions(player.getBounds(BoolVector::Y));
  sf::FloatRect newrect = player.getBounds(okayToMove);
    
  for (auto s : entities) {
    std::vector<EntityAction> actions = s->tick(queued_interactions.count(s)>0,
						newrect);
    for (EntityAction a : actions) {
      switch (a.type)
	{
	case ActionType::CancelMove:
	  okayToMove.x = false;
	  okayToMove.y = false;
	  newrect = player.getBounds(okayToMove);
	  break;
	case ActionType::RestrictInput :
	  mode = a.inputMode;
	  break;
	case ActionType::MovePlayer:
	  break;
	case ActionType::NewLevel:
	  res = TickResult(a.level);
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

  queued_interactions.clear();
  
  return res;
};

void Level::draw (sf::RenderTarget& target,
		  sf::RenderStates states) const {
  target.setView(viewport);
  target.draw(room.sprite, states);
  
#ifdef DEBUG_BUILD
  if (Debug::mode & 1) {
    for (sf::FloatRect r : bounds) {
      Debug::drawRect(r, sf::Color::Red, target, states);
    }
  }
#endif
      
  int lastz = -1;
  for (auto s : entities) {
    if (lastz < 0 && s->getZ() > 0) {
      player.drawOn(target, states);
    }
    lastz = s->getZ();
    s->drawOn(target, states);
  }
  if (lastz < 0) {
    player.drawOn(target, states);
  }
};
