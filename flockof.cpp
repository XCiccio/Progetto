#include "flockof.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>

position operator+(position const& a, position const& b)
{
  position sum{a};
  return sum += b;
}

position operator-(position const& a, position const& b)
{
  position sum{a};
  return sum -= b;
}

position operator/(position const& a, int N)
{
  return {(a.x) / N, (a.y) / N};
}

position operator*(double p, position const& a)
{
  return {(a.x) * p, (a.y) * p};
}

velocity operator+(velocity const& a, velocity const& b)
{
  velocity sum{a};
  return sum += b;
}
velocity operator-(velocity const& a, velocity const& b)
{
  velocity sum{a};
  return sum -= b;
}

velocity operator*(double a, velocity const& b)
{
  return {(b.v_x) * a, (b.v_y) * a};
}

double distance(position const& a, position const& b)
{
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

/*position vector_distance(position const& a, position const& b)
{
  return a - b;
}*/

velocity sum_of_velocity(velocity const& a, velocity const& b)
{
  return a + b;
}

position cm(std::vector<boid> const& boids, int N)
{
  position init{0.0, 0.0};
  position cm =
      std::accumulate(boids.begin(), boids.end(), init,
                      [](position res, boid a) { return res + a.pb; });
  /*auto cm_x = std::accumulate(boids.begin(), boids.end(), 0.,
                              [](double res, boid a) { return res + a.pb.x; });
  auto cm_y = std::accumulate(boids.begin(), boids.end(), 0.,
                              [](double res, boid a) { return res + a.pb.y; });
  */
  return (cm) / (N - 1);
}

velocity cohesion(double c, position const& CM, boid const& b)
{
  auto cohesion = c * (CM - b.pb);
  return {cohesion.x, cohesion.y};
  /*return {c * (vector_distance(CM, b.pb).x), c * (vector_distance(CM,
   * b.pb).y)};*/
}

velocity alignment(double a, boid const& b, std::vector<boid> const& v, int N)
{
  velocity init{0.0, 0.0};
  velocity result = std::accumulate(
      v.begin(), v.end(), init,
      [&b](velocity res, boid b_puff) { return res + (b_puff.vb - b.vb); });
  return (a / (N - 1)) * result;
  /*double sum_x =
      std::accumulate(v.begin(), v.end(), 0., [&b](double res, boid b_puff) {
        return res + (b_puff.vb.v_x - b.vb.v_x);
      });
  double sum_y =
      std::accumulate(v.begin(), v.end(), 0., [&b](double res, boid b_puff) {
        return res + (b_puff.vb.v_y - b.vb.v_y);
      });
  return {(a / (N - 1)) * sum_x, (a / (N - 1)) * sum_y};*/
}

velocity separation(double s, double ds, boid const& b,
                    std::vector<boid> const& v)
{
  position init{0.0, 0.0};
  position null_sum{0.0, 0.0};
  position result = std::accumulate(
      v.begin(), v.end(), init, [&b, ds, null_sum](position res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < ds ? res + (b_puff.pb - b.pb)
                                              : res + null_sum;
      });
  return {(-s) * result.x, (-s) * result.y};
  /*double sum_x = std::accumulate(
      v.begin(), v.end(), 0., [&b, ds](double res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < ds ? res + (b_puff.pb.x - b.pb.x)
                                              : res + 0.;
      });
  double sum_y = std::accumulate(
      v.begin(), v.end(), 0., [&b, ds](double res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < ds ? res + (b_puff.pb.y - b.pb.y)
                                              : res + 0.;
      });
  return {(-s) * sum_x, (-s) * sum_y};*/
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
    boid boid_puff = {random_position_generator(), random_velocity_generator()};
    v.push_back(boid_puff);
  }
  return v;
}

double d_m(std::vector<boid> v, int N)
{
  position c_m = cm(v, N);
  return (std::accumulate(
             v.begin(), v.end(), 0.,
             [c_m](double res, boid a) { return res + distance(a.pb, c_m); }))
       / N;
}
double v_m(std::vector<boid> v, int N)
{
  return (std::accumulate(
             v.begin(), v.end(), 0.,
             [](double res, boid a) { return res + a.vb.module(); }))
       / N;
}
