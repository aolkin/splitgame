
#include "entity.hpp"

#include "entities/tree.hpp"
  
EntityFactory::EntityFactory () {
  add_entity("Tree", &Entities::Tree::makeNew);
}
  
void EntityFactory::add_entity(const std::string s,
			       const MakerFunc& f) {
  entities[s] = f;
}
  
Entity* EntityFactory::make(const std::string type,
			    const std::vector<float> params,
			    const std::vector<std::string> sparams) {
  return entities[type](params, sparams);
}
