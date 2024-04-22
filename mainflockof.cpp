#include "flockof.hpp"
#include <iostream>

int main()
{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  std::vector v = boids_generator(N);
  for (int i = 0; i != N; i++) {
    std::cout << v[i].pb.x << " " << v[i].pb.y << " " << v[i].vb.v_x << " "
              << v[i].vb.v_y << '\n';
  }
}
