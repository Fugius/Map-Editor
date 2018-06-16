#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "creator/Create.h"

int main() {

  sf::RenderWindow window(sf::VideoMode(1280, 720), "Map Editor");
  window.setFramerateLimit(60);

  Create c(Vector2f(1280, 720));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        c.clear();
      }

      c.update(&event, &window);

    }

    window.clear();
    c.draw(&window);
    window.display();
  }

  return 0;
}
