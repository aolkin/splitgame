
#include "entity.hpp"

#include "entities/generic.hpp"
  
EntityFactory::EntityFactory () {
  add_entity("generic", &Entities::Generic::makeNew);
}
  
void EntityFactory::add_entity(const std::string s,
			       const MakerFunc& f) {
  entities[s] = f;
}
  
Entity* EntityFactory::make(const std::string& type,
			    const std::vector<float>& params,
			    const std::vector<std::string>& sparams) const {
  return entities.at(type)(params, sparams);
}
