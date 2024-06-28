#include "sfml_flockof.hpp"
#include <cassert>
#include <iostream>

int main()

{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  if (std::cin.fail() || std::cin.peek() != '\n') {
    return 1;
  }
  assert(N > 1);
  std::cout << "Insert the parameter s for separation \n";
  double s;
  std::cin >> s;
  if (!std::cin.good()) {
    return 1;
  }
  assert(s >= 0);
  std::cout << "Insert the parameter ds for minimum distance between boids \n";
  double ds;
  std::cin >> ds;
  if (!std::cin.good()) {
    return 1;
  }
  assert(ds >= 0);
  std::cout << "Insert the parameter a for alignment \n";
  double a;
  std::cin >> a;
  if (!std::cin.good()) {
    return 1;
  }
  assert(a >= 0);
  std::cout << "Insert the parameter c for cohesion \n";
  double c;
  std::cin >> c;
  if (!std::cin.good()) {
    return 1;
  }
  assert(c >= 0);
  sf::RenderWindow window(sf::VideoMode(800, 800), "FLOCK OF BOIDS");
  std::vector v = boids_generator(N);
  auto shapes   = create_shapes(v);
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    v = update_boids(v, s, ds, a, c, N);
    update_window(window, shapes, v);
  }
}
