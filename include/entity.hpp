#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <unordered_map>
#include <vector>
#include <string>

#include "sprite.hpp"
#include "global.hpp"

enum class ActionType { MovePlayer, ShowDialogue, RestrictInput, CancelMove };
  
struct EntityAction {
  ActionType type;
  union {
    struct {
      float offsetX;
      float offsetY;
    } movement;
    struct {
      int id;
    } dialogue;
    InputMode inputMode;
  };
};


class Entity : public Sprite {
public:
  int z;
  // TODO: fix this
  Entity (int zz) : Sprite(0,0), z(zz) { };
  virtual bool isSmall() { return false; };
  virtual std::vector<EntityAction> tick (const sf::FloatRect);
};

typedef Entity* (*MakerFunc)(const std::vector<float>,
			     const std::vector<std::string>);

class EntityFactory {
private:
  std::unordered_map<std::string, MakerFunc> entities;
  void add_entity(const std::string, const MakerFunc&);
public:
  EntityFactory ();
  Entity* make(const std::string, const std::vector<float>,
	       const std::vector<std::string>);
};

#endif
