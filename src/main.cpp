
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "input.hpp"
#include "level.hpp"
#include "player.hpp"

#include "extra/movie.hpp"

#include "entity.hpp"

namespace global {
  const std::string name = "SPLIT";
  const std::string splashfn = "split.mp4";
  const sf::Time delta = sf::seconds(.016666);
}

#ifdef DEBUG_BUILD
namespace Debug {
  int mode = 0;
  
  void drawRect(const sf::FloatRect& r, const sf::Color& color,
		sf::RenderTarget& target, sf::RenderStates states,
		int inset) {
    sf::RectangleShape rect(sf::Vector2f(r.width - 2 * inset,
					 r.height - 2 * inset));
    rect.setPosition(r.left + inset, r.top + inset);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(color);
    rect.setFillColor(sf::Color::Transparent);
    target.draw(rect, states);
  };
}
#endif

struct GameState {
  enum States { Game, Movie };
  enum LevelStates { Normal, FadingIn, FadingOut };
  States state;
  LevelStates level;
  float fadeProgress;
  int paused;
  std::unique_ptr<Level> active;
  std::unique_ptr<Level> next;
  class Movie movie;
  GameState(sf::RenderWindow& w, States s=Game) :
    state(s), paused(1), movie(w) { };
  void playMovie(std::string fn) {
    state = Movie;
    movie.start(fn);
  };
};

int main(int argc, char *argv[])
{
  using namespace global;

  sf::RenderWindow window;
  if (argc > 1)
    window.create(sf::VideoMode::getFullscreenModes()[0], name,
		  sf::Style::Fullscreen);
  else
    window.create(sf::VideoMode(width * 2, height * 2), name,
		  sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);

  sf::View defaultView = window.getDefaultView();
  
  // Initialization  

  Input::KeyMap keymap = Input::buildKeymap ();
  

  GameState state(window);
  state.playMovie(global::splashfn);
  state.active = Level::load(1, 0);
  state.active->activatePlayer();
  
  sf::Clock clock;
  sf::Time delta;
  
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (event.type == sf::Event::LostFocus)
	    state.paused++;
	  if (event.type == sf::Event::GainedFocus)
	    state.paused--;
	  if (event.type == sf::Event::KeyPressed) {
	    if (event.key.code == sf::Keyboard::Escape) {
	      if (state.state == GameState::Movie) {
		state.movie.stop();
	      }
	    }
	  }
	  state.active->handleInput(Input::getInput(event, keymap));
	}

      delta += clock.restart();

      window.setView(defaultView);

      switch (state.state) {
      case GameState::Movie:
	state.movie.update();
	if (state.movie.done()) {
	  state.state = GameState::Game;
	} else {
	  window.draw(state.movie);
	}
	break;
      case GameState::Game:
	if (state.paused == 0) {
	  TickResult result;
	  sf::Time dt = delta;
	  while (dt > global::delta) {
	    dt -= global::delta;
	    result = state.active->tick();
	    
	    switch (state.level) {
	    case GameState::FadingOut:
	      state.fadeProgress += .1f;
	      break;
	    case GameState::FadingIn:
	      state.fadeProgress -= .1f;
	      break;
	    default:
	      break;
	    }
	  }
	}
	
	window.clear(sf::Color::Black);
	window.draw(*state.active);

	if (state.level == GameState::FadingOut ||
	    state.level == GameState::FadingIn) {
	  window.clear(sf::Color(0, 0, 0, 255 * state.fadeProgress));
	}
	if (state.fadeProgress >= 1) {
	  state.level = GameState::FadingIn;
	  std::cout << state.active.get() << " " << state.next.get() << std::endl;
	  state.active = std::move(state.next);
	  std::cout << state.active.get() << " " << state.next.get() << std::endl;
	  state.active->activatePlayer();
	}
	break;
      }
      
      window.display();
      while (delta > global::delta) {
	delta -= global::delta;
      }
    }
  
  return 0;
}
