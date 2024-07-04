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
  std::cout << "Insert the parameter d for distance of interaction between boids \n";
  double d;
  std::cin >> d;
  if (!std::cin.good()) {
    return 1;
  }
  assert(d >= 0);
  std::cout << "Insert the parameter ds for minimum distance between boids \n";
  double ds;
  std::cin >> ds;
  if (!std::cin.good()) {
    return 1;
  }
  assert((ds >= 0) && (ds < d));
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
  const double min_position{10.};
  const double max_position{790.};
  const double max_velocity{100.};
  const double velocity_generation{70.};
  const double frame_rate_limit{1. / 60.};
  sf::RenderWindow window(sf::VideoMode(800, 800), "FLOCK OF BOIDS");
  std::vector v =
      boids_generator(N, min_position, max_position, velocity_generation);
  auto shapes = create_shapes(v);
  window.setFramerateLimit(60);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    v = update_boids(v, s, d, ds, a, c, min_position, max_position,
                     max_velocity, frame_rate_limit);
    update_window(window, shapes, v, static_cast<float>(min_position),
                  static_cast<float>(max_position));
    data positon_analysis  = position_data_analysis(v, N);
    data velocity_analysis = velocity_data_analysis(v, N);
    std::cout << "\rDistanza media dal centro di massa e velocità media: "
              << positon_analysis.mean << " +/- " << positon_analysis.sigma
              << "    " << velocity_analysis.mean << " +/- "
              << velocity_analysis.sigma;
  }
}
