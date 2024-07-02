#ifndef FLOCKOF_HPP
#define FLOCKOF_HPP
#include <math.h>
#include <chrono>
#include <memory>
#include <vector>

struct statistics
{
  double mean_distance;
  double mean_velocity;
};

struct data
{
  double mean;
  double sigma;
};

struct position
{
  double x;
  double y;
  position& operator+=(const position& p)
  {
    x = x + p.x;
    y = y + p.y;
    return *this;
  }
  position& operator-=(const position& p)
  {
    x = x - p.x;
    y = y - p.y;
    return *this;
  }
};

position operator+(position const&, position const&);

position operator-(position const&, position const&);

position operator/(position const&, int);

position operator*(position const&, double);

struct velocity
{
  double v_x;
  double v_y;
  double module()
  {
    return std::sqrt(std::pow(v_x, 2) + std::pow(v_y, 2));
  }
  velocity& operator+=(const velocity& v)
  {
    v_x = v_x + v.v_x;
    v_y = v_y + v.v_y;
    return *this;
  }
  velocity& operator-=(const velocity& v)
  {
    v_x = v_x - v.v_x;
    v_y = v_y - v.v_y;
    return *this;
  }
};

velocity operator+(velocity const&, velocity const&);

velocity operator-(velocity const&, velocity const&);

velocity operator*(double const, velocity const&);

class boid
{
 public:
  position pb;
  velocity vb;
};

double distance(position const&, position const&);

velocity sum_of_velocity(velocity const&, velocity const&);

position cm(std::vector<boid> const&, int);

velocity cohesion(int const N, double const, position const&, boid const&);

velocity cohesion(std::vector<boid> const&, int const, double const, boid const&);

velocity alignment(double const, boid const&, std::vector<boid> const&,
                   int const);

velocity separation(double const, double const, boid const&,
                    std::vector<boid> const&);

position random_position_generator(const double, const double);

velocity random_velocity_generator(const double);

std::vector<boid> boids_generator(int, const double, const double, const double);

velocity wall_repulsion(boid, const double, const double);

std::vector<boid> update_boids(std::vector<boid> &, double const, double const,
                               double const, double const, int const, const double, const double, const double, const double);

data position_data_analysis(std::vector<boid> const&, int const);

data velocity_data_analysis(std::vector<boid> const&, int const);


#endif
