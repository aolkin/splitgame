#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <SFML/Graphics.hpp>
#include <string>

#ifndef NO_SFEMOVIE

#include <sfeMovie/Movie.hpp>

class Movie : public sfe::Movie {
private:
  sf::Window& w;
public:
  Movie (sf::Window& window) : w(window) { };
  bool done ();
  bool start (std::string);
};

#else

class Movie : public sf::Drawable {
public:
  Movie (sf::Window& window) { };
  bool done () { return true; };
  bool start (std::string s) { return true; };
  void stop () { };
  void update () { };
  void draw (sf::RenderTarget &target, sf::RenderStates states) const { };
};
  
#endif
  
#endif
