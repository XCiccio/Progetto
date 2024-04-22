#ifndef FLOCKOF_HPP
#define FLOCKOF_HPP
#include <vector>

struct position
{
  double x;
  double y;
};

struct velocity
{
  double v_x;
  double v_y;
};

class boid
{
 public:
  position pb;
  velocity vb;
};

double distance(position const&, position const&);

position vector_distance(position const&, position const&);

velocity sum_of_velocity(velocity const&, velocity const&);

position cm(std::vector<boid> const&, int);

velocity cohesion(double, position const&, boid const&);

velocity alignment(double, boid const&, std::vector<boid> const&, int);

velocity separation(double, double, boid const&, std::vector<boid> const&);

position random_position_generator();

velocity random_velocity_generator();

std::vector<boid> boids_generator(int);

#endif
