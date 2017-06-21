#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <SFML/Graphics.hpp>

enum class InputMode { None, Player, Dialogue, Menu };

namespace global {
  const float width = 480;
  const float height = 270;
}

struct NewLevel {
  int id;
  int start;
  NewLevel (int i, int s) : id(i), start(s) { };
};

#ifdef DEBUG_BUILD
namespace Debug {
  extern int mode;
  void drawRect(const sf::FloatRect&, const sf::Color&,
		sf::RenderTarget&, sf::RenderStates, int=1);
}
#include <iostream>
#endif

#endif
