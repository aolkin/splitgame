#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>
#include <string>

class Movie : public sfe::Movie {
private:
  sf::Window& w;
public:
  Movie (sf::Window& window) : w(window) { };
  bool done ();
  bool start (std::string);
};
  
#endif
