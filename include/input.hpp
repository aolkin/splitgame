#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <SFML/Window.hpp>

#include "global.hpp"

namespace Input {
  enum Inputs { None, Left, Right, Up, Down, Okay, Cancel };
  
  struct Event {
    Inputs type;
    bool release;
    Event () : type(None) { };
    Event (Inputs i, bool r) : type(i), release(r) { };
  };
  
  typedef std::unordered_map<int, Inputs> KeyMap;
  
  KeyMap buildKeymap ();
  Event getInput(const sf::Event&, KeyMap&);
}

#endif
