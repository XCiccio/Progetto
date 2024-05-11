#include "sfml_flockof.hpp"
#include <iostream>

int main()

{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  std::cout << "Insert the parameter s for separation \n";
  double s;
  std::cin >> s;
  std::cout << "Insert the parameter ds for minimum distance between boids \n";
  double ds;
  std::cin >> ds;
  std::cout << "Insert the parameter a for alignment \n";
  double a;
  std::cin >> a;
  std::cout << "Insert the parameter c for cohesion \n";
  double c;
  std::cin >> c;
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
