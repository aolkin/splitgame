
#include "input.hpp"

namespace Input {
  using namespace Input;
  KeyMap buildKeymap () {
    KeyMap keymap;
    keymap[sf::Keyboard::Left] = Input::Left;
    keymap[sf::Keyboard::Right] = Input::Right;
    keymap[sf::Keyboard::Down] = Input::Down;
    keymap[sf::Keyboard::Up] = Input::Up;
    keymap[sf::Keyboard::A] = Input::Left;
    keymap[sf::Keyboard::D] = Input::Right;
    keymap[sf::Keyboard::S] = Input::Down;
    keymap[sf::Keyboard::W] = Input::Up;
    keymap[sf::Keyboard::J] = Input::Okay;
    keymap[sf::Keyboard::K] = Input::Cancel;
    keymap[sf::Keyboard::Return] = Input::Okay;
    keymap[sf::Keyboard::RShift] = Input::Cancel;
    return keymap;
  }
  
  Event getInput (const sf::Event& event, KeyMap& keymap) {
    if (event.type == sf::Event::KeyPressed) {
      #ifdef DEBUG_BUILD
      if (event.key.code == sf::Keyboard::PageDown)
	Debug::mode--;
      else if (event.key.code == sf::Keyboard::PageUp)
	Debug::mode++;
      #endif
      return Event(keymap[event.key.code], false);
    }
    else if (event.type == sf::Event::KeyReleased)
      return Event(keymap[event.key.code], true);
    else
      return Event();
  }
}
