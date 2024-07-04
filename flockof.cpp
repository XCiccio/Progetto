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

position cm(std::vector<boid> const& v, int const N)
{
  position init{0.0, 0.0};
  position cm = (std::accumulate(
                    v.begin(), v.end(), init,
                    [](position res, boid b_puff) { return res + b_puff.pb; }))
              / (N);
  return cm;
}

velocity cohesion(std::vector<boid> const& v, boid const& b, double const d,
                  double const c, int const count)
{
  position init{0., 0.};
  position const null_sum{0.0, 0.0};
  position cm = (std::accumulate(v.begin(), v.end(), init,
                                 [&b, d, &null_sum](position res, boid b_puff) {
                                   return distance(b.pb, b_puff.pb) < d
                                            ? res + b_puff.pb
                                            : res + null_sum;
                                 })
                 - b.pb)
              / (count);
  auto cohesion = (cm - b.pb) * c;
  return {cohesion.x, cohesion.y};
}

velocity alignment(std::vector<boid> const& v, boid const& b, double const d,
                   double const a, int const count)
{
  velocity init{0.0, 0.0};
  velocity const null_sum{0.0, 0.0};
  velocity result = std::accumulate(
      v.begin(), v.end(), init, [&b, d, &null_sum](velocity res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < d ? res + (b_puff.vb - b.vb)
                                             : res + null_sum;
      });
  return (a / count) * result;
}

velocity separation(std::vector<boid> const& v, boid const& b, double const s,
                    double const ds)
{
  position init{0.0, 0.0};
  position const null_sum{0.0, 0.0};
  position result = std::accumulate(
      v.begin(), v.end(), init, [&b, ds, &null_sum](position res, boid b_puff) {
        return distance(b.pb, b_puff.pb) < ds ? res + (b_puff.pb - b.pb)
                                              : res + null_sum;
      });
  return {result.x * (-s), result.y * (-s)};
}

position random_position_generator(double const min_position,
                                   double const max_position)
{
  int const N = 2;
  std::vector<double> v;
  v.reserve(N);
  auto seed = static_cast<long unsigned int>(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::default_random_engine generator(seed);
  std::generate_n(std::back_inserter(v), N, [&] {
    std::uniform_real_distribution<double> dist(min_position, max_position);
    return dist(generator);
  });
  return {v[0], v[1]};
}

velocity random_velocity_generator(double const velocity_generation)
{
  int const N = 2;
  std::vector<double> v;
  v.reserve(N);
  auto seed = static_cast<long unsigned int>(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::default_random_engine generator(seed);
  std::generate_n(std::back_inserter(v), N, [&] {
    std::uniform_real_distribution<double> dist(-velocity_generation,
                                                velocity_generation);
    return dist(generator);
  });
  return {v[0], v[1]};
}

std::vector<boid> boids_generator(int const N, double const min_position,
                                  double const max_position,
                                  double const velocity_generation)
{
  std::vector<boid> v;
  v.reserve(static_cast<long unsigned int>(N));
  for (long unsigned int it{0}; it != static_cast<long unsigned int>(N); ++it) {
    boid boid_puff = {random_position_generator(min_position, max_position),
                      random_velocity_generator(velocity_generation)};
    v.push_back(boid_puff);
  }
  return v;
}

velocity wall_repulsion(boid& boid, double const min_position,
                        double const max_position)
{
  if ((boid.pb.x > max_position && boid.vb.v_x > 0 && boid.pb.y > max_position
       && boid.vb.v_y > 0)
      || (boid.pb.x < min_position && boid.vb.v_x < 0
          && boid.pb.y < min_position && boid.vb.v_y < 0)
      || (boid.pb.x > max_position && boid.vb.v_x > 0
          && boid.pb.y < min_position && boid.vb.v_y < 0)
      || (boid.pb.x < min_position && boid.vb.v_x < 0
          && boid.pb.y > max_position && boid.vb.v_y > 0)) {
    boid.vb = {-boid.vb.v_x, -boid.vb.v_y};
  } else if ((boid.pb.x > max_position && boid.vb.v_x > 0)
             || (boid.pb.x < min_position && boid.vb.v_x < 0)) {
    boid.vb = {-boid.vb.v_x, boid.vb.v_y};
  } else if ((boid.pb.y > max_position && boid.vb.v_y > 0)
             || (boid.pb.y < min_position && boid.vb.v_y < 0)) {
    boid.vb = {boid.vb.v_x, -boid.vb.v_y};
  }
  return boid.vb;
}

std::vector<boid> update_boids(std::vector<boid> const& v, double const s,
                               double const d, double const ds, double const a,
                               double const c, double const min_position,
                               double const max_position,
                               double const max_velocity,
                               double const frame_rate_limit)
{
  std::vector<boid> v1 = v;
  for (auto& boid : v1) {
    if (boid.pb.x > max_position || boid.pb.x < min_position
        || boid.pb.y > max_position || boid.pb.y < min_position) {
      boid.vb                = wall_repulsion(boid, min_position, max_position);
      auto position_velocity = frame_rate_limit * boid.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid.pb += new_position;
    } else {
      auto boid1 = boid;
      int count =
          static_cast<int>(std::count_if(
              v.begin(), v.end(),
              [&boid, d](auto bb) { return distance(boid.pb, bb.pb) < d; }))
          - 1;
      if (count > 0) {
        boid.vb += separation(v, boid, s, ds) + alignment(v, boid, d, a, count)
                 + cohesion(v, boid, d, c, count);

        if (boid.vb.module() >= max_velocity) {
          boid.vb = boid1.vb;
        }
      }
      auto position_velocity = frame_rate_limit * boid.vb;
      position new_position{position_velocity.v_x, position_velocity.v_y};
      boid.pb += new_position;
    }
  }
  return v1;
}

data position_data_analysis(std::vector<boid> const& v, int const N)
{
  auto mean = (std::accumulate(v.begin(), v.end(), 0.,
                               [&v, N](double res, boid b_puff) {
                                 return res + distance(b_puff.pb, cm(v, N));
                               }))
            / N;
  auto sum = std::accumulate(
      v.begin(), v.end(), 0., [&v, N, mean](double res, boid b_puff) {
        return res + std::pow(distance(b_puff.pb, cm(v, N)) - mean, 2);
      });
  auto sigma = std::sqrt(sum / (N - 1));
  return {mean, sigma};
}

data velocity_data_analysis(std::vector<boid> const& v, int const N)
{
  auto mean = (std::accumulate(v.begin(), v.end(), 0.,
                               [&v](double res, boid b_puff) {
                                 return res + b_puff.vb.module();
                               }))
            / N;
  auto sum = std::accumulate(
      v.begin(), v.end(), 0., [&v, mean](double res, boid b_puff) {
        return res + std::pow(b_puff.vb.module() - mean, 2);
      });
  auto sigma(std::sqrt(sum / (N - 1)));
  return {mean, sigma};
}
