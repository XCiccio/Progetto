#include "flockof.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <numeric>

double distance(position const& a, position const& b)
{
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

position vector_distance(position const& a, position const& b)
{
  return {a.x - b.x, a.y - b.y};
}

velocity sum_of_velocity(velocity const& a, velocity const& b)
{
  return {a.v_x + b.v_x, a.v_y + b.v_y};
}

position cm(std::vector<boid> const& boids, int N)
{
  auto cm_x = std::accumulate(boids.begin(), boids.end(), 0.,
                              [](double res, boid a) { return res + a.pb.x; });
  auto cm_y = std::accumulate(boids.begin(), boids.end(), 0.,
                              [](double res, boid a) { return res + a.pb.y; });
  return {(cm_x) / (N - 1), (cm_y) / (N - 1)};
}

velocity cohesion(double c, position const& CM, boid const& b)
{
  return {c * (vector_distance(CM, b.pb).x), c * (vector_distance(CM, b.pb).y)};
}
