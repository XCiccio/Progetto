#include "flockof.hpp"
#include <chrono>
#include <iostream>
int main()

{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  std::vector v = boids_generator(N);
  std::cout << "That's the size of your vector " << v.size() << '\n';
  /*for (auto it = v.begin(), last = v.end(); it != last; ++it) {
    auto boid = *it;
    std::cout << boid.pb.x << boid.pb.y << '\n';
  }*/
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
  auto start = std::chrono::steady_clock::now();
  for (;;) {
    auto now = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    if (duration >= desired_duration_seconds) {
      break;
    }
    for (auto it = v.begin(), end = v.end(); it != end; ++it) {
      auto& boid = *it;
      std::cout << boid.pb.x << " " << boid.pb.y << " " << '\n';
      boid.vb = boid.vb + separation(s, ds, boid, v) + alignment(a, boid, v, N)
              + cohesion(c, cm(v, N), boid);
      auto time_lasted = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::steady_clock::now() - now)
                             .count();
      auto position_velocity = static_cast<double>(time_lasted) * boid.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid.pb = boid.pb + new_position;
    }
  }
  std::cout << "The mean velocity is " << v_m(v, N) << '\n';
  std::cout << "The mean distance by the cm is " << d_m(v, N) << '\n';
}

