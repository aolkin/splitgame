#ifndef FACTORY_H
#define FACTORY_H

#include <unordered_map>
#include <vector>
#include <string>

#include "entity.hpp"

class EntityFactory {
private:
  std::unordered_map<std::string, MakerFunc> entities;
  void add_entity(const std::string, const MakerFunc&);
public:
  EntityFactory ();
  Entity* make(const std::string, const std::vector<int>);
};


#endif
