#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "sprite.hpp"

enum class InputMode { None, Player, Dialogue };
    
enum class ActionType { MovePlayer, ShowDialogue, RestrictInput };
  
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
  void tick () { doTick(); };
  virtual bool isSmall() { return false; };
  virtual std::vector<EntityAction> doTick ();
};

typedef Entity* (*MakerFunc)(const std::vector<int>);

#endif
