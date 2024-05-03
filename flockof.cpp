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

velocity sum_of_velocity(velocity const& a, velocity const& b)
{
  return a + b;
}

position cm(std::vector<boid> const& boids, int const N)
{
  position init{0.0, 0.0};
  position cm =
      std::accumulate(boids.begin(), boids.end(), init,
                      [](position res, boid a) { return res + a.pb; });
  return (cm) / (N - 1);
}

velocity cohesion(double const c, position const& CM, boid const& b)
{
  auto cohesion = c * (CM - b.pb);
  return {cohesion.x, cohesion.y};
}

velocity alignment(double const a, boid const& b, std::vector<boid> const& v,
                   int const N)
{
  velocity init{0.0, 0.0};
  velocity result = std::accumulate(
      v.begin(), v.end(), init,
      [&b](velocity res, boid b_puff) { return res + (b_puff.vb - b.vb); });
  return (a / (N - 1)) * result;
}

velocity separation(double const s, double const ds, boid const& b,
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
    std::uniform_real_distribution<double> dist(-3, 3);
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
    std::uniform_real_distribution<double> dist(-2, 2);
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

std::vector<boid>
update_boids(std::chrono::_V2::steady_clock::time_point::rep time_lasted,
             std::vector<boid>& v, double s, double ds, double a, double c,
             int N)
{
  for (auto it = v.begin(), end = v.end(); it != end; ++it) {
    auto boid_1 = *it;
    boid boid_2;
    if (boid_1.pb.x > 4 || boid_1.pb.x < -4 || boid_1.pb.y > 4
        || boid_1.pb.y < -4) {
      boid_2.vb = -1 * boid_1.vb;
      auto position_velocity =
          (static_cast<double>(time_lasted) * 0.00000001) * boid_2.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid_2.pb = boid_1.pb + new_position;
      *it       = boid_2;
    } else {
      boid_2.vb =
          ((boid_1.vb + separation(s, ds, boid_1, v))
           + (alignment(a, boid_1, v, N) + cohesion(c, cm(v, N), boid_1)));

      if (boid_2.vb.module() >= 10.) {
        boid_2.vb = boid_1.vb;
      }

      auto position_velocity =
          (static_cast<double>(time_lasted) * 0.00000001) * boid_2.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid_2.pb = boid_1.pb + new_position;
      *it       = boid_2;
    }
  }
  return v;
}

data position_data_analysis(std::vector<boid> const& v, int const N)
{
  auto mean = (std::accumulate(v.begin(), v.end(), 0.,
                               [&v, N](double res, boid a) {
                                 return res + distance(a.pb, cm(v, N));
                               }))
            / N;
  auto sum = std::accumulate(
      v.begin(), v.end(), 0., [&v, N, mean](double res, boid a) {
        return res + std::pow(distance(a.pb, cm(v, N)) - mean, 2);
      });
  auto sigma = std::sqrt(sum / (N - 1));
  return {mean, sigma};
}

data velocity_data_analysis(std::vector<boid> const& v, int const N)
{
  auto mean = (std::accumulate(
                  v.begin(), v.end(), 0.,
                  [&v](double res, boid a) { return res + a.vb.module(); }))
            / N;
  auto sum =
      std::accumulate(v.begin(), v.end(), 0., [&v, mean](double res, boid a) {
        return res + std::pow(a.vb.module() - mean, 2);
      });
  auto sigma(std::sqrt(sum / (N - 1)));
  return {mean, sigma};
}
