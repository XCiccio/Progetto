#include "flockof.hpp"
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
  std::vector v = boids_generator(N);
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
    } else {
      for (auto it = v.begin(), end = v.end(); it != end; ++it) {
        auto boid = *it;
        boid.vb   = boid.vb + separation(s, ds, boid, v)
                + alignment(a, boid, v, N) + cohesion(c, cm(v, N), boid);
      }
    }
  }
}


