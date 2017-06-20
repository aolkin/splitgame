#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <unordered_map>
#include <vector>
#include <string>

#include "sprite.hpp"
#include "global.hpp"

enum class ActionType { MovePlayer, ShowDialogue, RestrictInput, CancelMove,
    NewLevel };

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
    NewLevelStruct level;
    InputMode inputMode;
  };
};


class Entity : public Sprite {
protected:
  int z;
  bool silentTickNeedsCollision;
  std::vector<sf::FloatRect> bounds;
  void addDefaultBoundary();
public:
  int getZ() { return z; };
  Entity (float w, float h, int zz, bool stick=false) :
    Sprite(w,h), z(zz), silentTickNeedsCollision(stick) { };
  virtual bool isSmall() const { return false; };
  virtual bool hasCollided(const sf::FloatRect&);
  virtual bool isPassable() const { return true; };
  virtual void silentTick() { };
  virtual void silentTick(bool) { };
  virtual std::vector<EntityAction> tick (const sf::FloatRect&);
  void drawOn(sf::RenderTarget& target, sf::RenderStates states) const;
};

const std::string ENTITY_ART = "art/entity/";

typedef Entity* (*MakerFunc)(const std::vector<float>&,
			     const std::vector<std::string>&);

class EntityFactory {
private:
  std::unordered_map<std::string, MakerFunc> entities;
  void add_entity(const std::string, const MakerFunc&);
public:
  EntityFactory ();
  Entity* make(const std::string&, const std::vector<float>&,
	       const std::vector<std::string>&) const;
};

#endif
