
#include "extra/movie.hpp"

bool Movie::start (std::string fn) {
  bool result = openFromFile(fn);
  if (!result) { return false; }
  auto windowSize = w.getSize();
  fit(0, 0, windowSize.x, windowSize.y);
  play();
  return true;
}

bool Movie::done () {
  return (getStatus() == sfe::Stopped);
    
}
