
#include "entity.hpp"

#include "entities/generic.hpp"
#include "entities/traveler.hpp"
#include "entities/parallax.hpp"
  
EntityFactory::EntityFactory () {
  add_entity("generic", &Entities::Generic::makeNew);
  add_entity("traveler", &Entities::Traveler::makeNew);
  add_entity("parallax", &Entities::Parallax::makeNew);
}
  
void EntityFactory::add_entity(const std::string s,
			       const MakerFunc& f) {
  entities[s] = f;
}
  
std::shared_ptr<Entity> EntityFactory::make(const std::string& type,
					    const std::vector<float>& params,
					    const std::vector<std::string>&
					    sparams) const {
  return std::shared_ptr<Entity>(entities.at(type)(params, sparams));
}

const EntityFactory& EntityFactory::singleton() {
  static const EntityFactory entity_factory;
  return entity_factory;
};
