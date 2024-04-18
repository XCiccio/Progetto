#include <math.h>
#include "flockof.hpp"


struct position{
    double x;
    double y;
};

struct velocity{
    double v_x;
    double v_y;
};

double sum_of_position(position const& a, position const& b){
    return std::sqrt(std::pow(a.x-b.x,2)+std::pow(a.y-b.y,2));
}

velocity sum_of_velocity(velocity a, velocity b){
    return {a.v_x+b.v_x, a.v_y+b.v_y};
}
