#include "flockof.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

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

velocity alignment(double a, boid const& b, std::vector<boid> const& v, int N)
{
  double sum_x =
      std::accumulate(v.begin(), v.end(), 0., [&b](double res, boid b_puff) {
        return res + (b_puff.vb.v_x - b.vb.v_x);
      });
  double sum_y =
      std::accumulate(v.begin(), v.end(), 0., [&b](double res, boid b_puff) {
        return res + (b_puff.vb.v_y - b.vb.v_y);
      });
  return {(a / (N - 1)) * sum_x, (a / (N - 1)) * sum_y};
}

velocity separation(double s, double ds, boid const& b,
                    std::vector<boid> const& v)
{
  double sum_x = std::accumulate(
      v.begin(), v.end(), 0., [&b, ds](double res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < ds ? res + (b_puff.pb.x - b.pb.x)
                                              : res + 0.;
      });
  double sum_y = std::accumulate(
      v.begin(), v.end(), 0., [&b, ds](double res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < ds ? res + (b_puff.pb.y - b.pb.y)
                                              : res + 0.;
      });
  return {(-s) * sum_x, (-s) * sum_y};
}


position random_position_generator()
{
  int const N = 2;
  std::vector<double> v;
  v.reserve(N);
  auto seed = static_cast<long unsigned int>(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::default_random_engine generator(seed);
  std::generate_n(std::back_inserter(v), N, [&] {
    std::uniform_real_distribution<double> dist(-5, 5);
    return dist(generator);
  });
  return {v[0], v[1]};
}

velocity random_velocity_generator()
{
  int const N = 2;
  std::vector<double> v;
  v.reserve(N);
  auto seed = static_cast<long unsigned int>(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::default_random_engine generator(seed);
  std::generate_n(std::back_inserter(v), N, [&] {
    std::uniform_real_distribution<double> dist(-5, 5);
    return dist(generator);
  });
  return {v[0], v[1]};
}

std::vector<boid> boids_generator(int const N)
{
  std::vector<boid> v;
  v.reserve(static_cast<long unsigned int>(N));
  for (long unsigned int it{0}; it != static_cast<long unsigned int>(N); ++it) {
    v[it] = {random_position_generator(), random_velocity_generator()};
  }
  return v;
}

