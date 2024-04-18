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

#endif
