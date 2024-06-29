#include "flockof.hpp"
#include <algorithm>
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

position operator*(position const& a, double p)
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
  auto cohesion = (CM - b.pb) * c;
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
  return {result.x * (-s), result.y * (-s)};
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
    std::uniform_real_distribution<double> dist(15, 785);
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
    std::uniform_real_distribution<double> dist(-20, 20);
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

velocity wall_repulsion(boid& boid)
{
  auto boid1 = boid;
  if ((boid.pb.x > 790 && boid.vb.v_x > 0 && boid.pb.y > 790 && boid.vb.v_y > 0)
      || (boid.pb.x < 10 && boid.vb.v_x < 0 && boid.pb.y < 10
          && boid.vb.v_y < 0)
      || (boid.pb.x > 790 && boid.vb.v_x > 0 && boid.pb.y < 10
          && boid.vb.v_y < 0)
      || (boid.pb.x < 10 && boid.vb.v_x < 0 && boid.pb.y > 790
          && boid.vb.v_y > 0)) {
    boid1.vb = {-1 * boid.vb.v_x, -1 * boid.vb.v_y};
  } else if ((boid.pb.x > 790 && boid.vb.v_x > 0)
             || (boid.pb.x < 10 && boid.vb.v_x < 0)) {
    boid1.vb = {-1 * boid.vb.v_x, boid.vb.v_y};
  } else if ((boid.pb.y > 790 && boid.vb.v_y > 0)
             || (boid.pb.y < 10 && boid.vb.v_y < 0)) {
    boid1.vb = {boid.vb.v_x, -1 * boid.vb.v_y};
  }
  return boid1.vb;
}

std::vector<boid> update_boids(std::vector<boid>& v, double s, double ds,
                               double a, double c, int N)
{
  for (auto& boid : v) {
    if (boid.pb.x > 790 || boid.pb.x < 10 || boid.pb.y > 790
        || boid.pb.y < 10) {
      boid.vb                = wall_repulsion(boid);
      auto position_velocity = (1. / 60.) * boid.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid.pb += new_position;
    } else {
      auto boid1 = boid;
      boid.vb += separation(s, ds, boid, v) + alignment(a, boid, v, N)
               + cohesion(c, cm(v, N), boid);

      if (boid.vb.module() >= 50.) {
        boid.vb = boid1.vb;
      }

      auto position_velocity = (1. / 60.) * boid.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid.pb += new_position;
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
