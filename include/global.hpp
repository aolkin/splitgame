#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <SFML/Graphics.hpp>

enum class InputMode { None, Player, Dialogue, Menu };
enum class Mode { Unsplit = 0, Creative = 2, Logical = 3 };

namespace global {
  const float width = 480;
  const float height = 270;
}

struct NewLevelStruct {
  int id;
  int start;
};

#ifdef DEBUG_BUILD
namespace Debug {
  extern int mode;
  void drawRect(const sf::FloatRect&, const sf::Color&,
		sf::RenderTarget& target, sf::RenderStates states);
}
#endif

#endif
