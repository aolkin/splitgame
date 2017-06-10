
#include "entity_factory.hpp"

#include "entities/tree.hpp"
  
EntityFactory::EntityFactory () {
  add_entity("Tree", &Entities::Tree::makeNew);
}
  
void EntityFactory::add_entity(const std::string s,
			       const MakerFunc& f) {
  entities[s] = f;
}
  
Entity* EntityFactory::make(const std::string type,
			    const std::vector<int> params) {
  return entities[type](params);
}


