#include "flockof.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

int main()

{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  std::vector v = boids_generator(N);
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
  std::cout << "How many seconds do you want the program to last? \n";
  int desired_duration_seconds;
  std::cin >> desired_duration_seconds;
  // sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  /*sf::RectangleShape boid;
  sf::Vector2f boidposition(v[0].pb.x, v[0].pb.y);
  boid.setPosition(boidposition);
  boid.setSize(sf::Vector2f(50, 50));*/
  auto start = std::chrono::steady_clock::now();
  // std::vector<boid> v_updated;
  //  while (window.isOpen())

  for (;;) {
    auto now = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    if (duration >= desired_duration_seconds) {
      break;
    }
    auto time_lasted = std::chrono::duration_cast<std::chrono::nanoseconds>(
                           std::chrono::steady_clock::now() - now)
                           .count();
    auto v_updated = update_boids(time_lasted, v, s, ds, a, c, N);
    v              = v_updated;
    std::cout << "Distanza media intermedia dal cm " << d_m(v, N) << '\n';
    /*window.clear();
    window.draw(boid);
    window.display();*/
    // window.close();
  }
}

// std::this_thread::sleep_for(std::chrono::milliseconds(500));
//  }
