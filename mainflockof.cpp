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
  //  while (window.isOpen()) {
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
    for (auto it = v.begin(), end = v.end(); it != end; ++it) {
      auto boid = *it;
      std::cout << "Velocity " << boid.vb.v_x << " " << boid.vb.v_y << '\n';
      boid.vb = ((boid.vb + separation(s, ds, boid, v))
                 + (alignment(a, boid, v, N) + cohesion(c, cm(v, N), boid)));
      // std::cout << "Position" << boid.pb.x << " " << boid.pb.y << '\n';
      // std::cout << "Separation " << separation(s, ds, boid, v).v_x << " "
      //<< separation(s, ds, boid, v).v_y << '\n';
      std::cout << "Alignment " << alignment(a, boid, v, N).v_x << " "
                << alignment(a, boid, v, N).v_y << '\n';
      std::cout << "Cohesion " << cohesion(c, cm(v, N), boid).v_x << " "
                << cohesion(c, cm(v, N), boid).v_y << '\n';
      std::cout << "Velocity " << boid.vb.v_x << " " << boid.vb.v_y << '\n';
      std::cout << (alignment(a, boid, v, N) + cohesion(c, cm(v, N), boid)
                    + separation(s, ds, boid, v))
                       .v_x
                << '\n';
      // std::cout << "Cm" << cm(v, N).x << " " << cm(v, N).y << '\n';
      // std::cout << "Cohesion " << cohesion(c, cm(v, N), boid).v_x << " "
      //<< cohesion(c, cm(v, N), boid).v_y << '\n';
      // std::cout << " Questa è distanza media dal centro di massa" << d_m(v,
      // N)
      //<< " " << '\n';
      auto position_velocity =
          (static_cast<double>(time_lasted) * 0.00000001) * boid.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid.pb = boid.pb + new_position;
      *it     = boid;
      //  v_updated = update_boids(now, v, s, ds, a, c, N);
      /*window.clear();
      window.draw(boid);
      window.display();*/
      // window.close();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //}
  }
}


