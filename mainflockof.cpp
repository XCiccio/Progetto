#include "flockof.hpp"
#include <iostream>

int main()
{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  double s;
  double ds;
  double a;
  double c;
  std::vector v = boids_generator(N);
  for (auto it = v.begin(), end = v.end(); it != end; ++it) {
    auto boid = *it;
    boid.vb   = boid.vb + separation(s, ds, boid, v) +
  }
}

