#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#include "sprite.hpp"
#include "global.hpp"

enum class ActionType { Ignore, MovePlayer, ShowDialogue, RestrictInput,
    CancelMove, NewLevel };

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
    NewLevel level;
    InputMode inputMode;
  };
  EntityAction () : type(ActionType::Ignore) { };
  EntityAction (float x, float y) : type(ActionType::MovePlayer) {
    movement.offsetX = x;
    movement.offsetY = y;
  };
  EntityAction (NewLevel nl) : type(ActionType::NewLevel), level(nl) { };
  EntityAction (InputMode i) : type(ActionType::RestrictInput),
			       inputMode(i) { };
};

class Entity : public Sprite {
public:
  enum TickMode { Silent, SilentRect,
		  Action, ActionRect };
protected:
  int z;
  TickMode tickMode;
  std::vector<sf::FloatRect> bounds;
  void addDefaultBoundary();
public:
  int getZ() { return z; };
  Entity (float w, float h, int zz, TickMode tickm=Silent) :
    Sprite(w,h), z(zz), tickMode(tickm) { };
  virtual bool isSmall() const { return false; };
  virtual bool hasCollided(const sf::FloatRect&);
  virtual bool isPassable() const { return true; };
  
  virtual void silentTick() { };
  virtual void silentTick(const sf::FloatRect&) { };
  virtual EntityAction oneTick() { return EntityAction(); };
  virtual EntityAction oneTick(const sf::FloatRect&) {
    return EntityAction();
  };
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
  std::shared_ptr<Entity> make(const std::string&, const std::vector<float>&,
			       const std::vector<std::string>&) const;
};

const extern EntityFactory entity_factory;

#endif
