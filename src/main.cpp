
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

  /** The game will run in V-sync mode, but will tick the game based on
   * this constant. */
  const float FPS = 60.f;
  /** Length of time to fade out and back in when loading a new level,
   * in seconds. */
  const float FADE_SPEED = .6f;
  
  const sf::Time delta = sf::seconds(1.f / FPS);
  const float fade_increment = 2 / (FPS * FADE_SPEED);
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
  NewLevel next;
  class Movie movie;
  GameState(sf::RenderWindow& w, States s=Game) :
    state(s), paused(1), next(0, 0), movie(w) { };
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
  sf::View scaledView(sf::FloatRect(0, 0, width, height));
  scaledView.setViewport(sf::FloatRect(0, 0, 1, 1));
  sf::RectangleShape fadeRect(sf::Vector2f(width, height));
  
  // Initialization  

  Input::KeyMap keymap = Input::buildKeymap ();
  Player::singleton();
  EntityFactory::singleton();

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

	    if (state.level == GameState::Normal &&
		result.type == TickResult::NewLevel) {
	      state.next = result.level;
	      state.level = GameState::FadingOut;
	    }
	    
	    switch (state.level) {
	    case GameState::FadingOut:
	      state.fadeProgress += fade_increment;
	      break;
	    case GameState::FadingIn:
	      state.fadeProgress -= fade_increment;
	      break;
	    default:
	      break;
	    }
	    
	    if (state.fadeProgress <= 0 &&
		state.level == GameState::FadingIn) {
	      state.level = GameState::Normal;
	      state.fadeProgress = 0;
	    }
	    if (state.fadeProgress >= 1) {
	      state.fadeProgress = 1;
	      state.level = GameState::FadingIn;
	      std::unique_ptr<Level> next = Level::load(state.next);
	      // DISCARD OLD LEVEL
	      state.active = std::move(next);
	      state.active->activatePlayer();
	    }
	  }
	}
	
	window.clear(sf::Color::Black);
	window.draw(*state.active);

	if (state.level == GameState::FadingOut ||
	    state.level == GameState::FadingIn) {
	  fadeRect.setFillColor(sf::Color(0, 0, 0, 255 * state.fadeProgress));
	  window.setView(scaledView);
	  window.draw(fadeRect);
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
