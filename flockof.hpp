#ifndef FLOCKOF_HPP
#define FLOCKOF_HPP
#include <math.h>
#include <vector>

struct statistics
{
  double mean_distance;
  double mean_velocity;
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

velocity operator*(double, velocity const&);

class boid
{
 public:
  position pb;
  velocity vb;
};

double distance(position const&, position const&);

/*position vector_distance(position const&, position const&);*/

velocity sum_of_velocity(velocity const&, velocity const&);

position cm(std::vector<boid> const&, int);

velocity cohesion(double, position const&, boid const&);

velocity alignment(double, boid const&, std::vector<boid> const&, int);

velocity separation(double, double, boid const&, std::vector<boid> const&);

position random_position_generator();

velocity random_velocity_generator();

std::vector<boid> boids_generator(int);

double d_m(std::vector<boid>, int);

double v_m(std::vector<boid>, int);

#endif
