#include <math.h>
#include "flockof.hpp"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>



struct position{
    double x;
    double y;
};

struct velocity{
    double v_x;
    double v_y;
};

class boid{
public:
   velocity vb;
   position xb;
};

double distance(position const& a, position const& b){
    return std::sqrt(std::pow(a.x-b.x,2)+std::pow(a.y-b.y,2));
}

position vector_distance(position const& a, position const& b){
    return {a.x-b.x, a.y-b.y};
}

velocity sum_of_velocity(velocity a, velocity b){
    return {a.v_x+b.v_x, a.v_y+b.v_y};
}

position cm(std::vector<position> const& boids, int N){
    auto cm_x = std::accumulate(boids.begin(),boids.end(),0.,[](double res, position a){return res + a.x;});
    auto cm_y = std::accumulate(boids.begin(), boids.end(), 0., [](double res, position a){return res + a.y;});
    return {(cm_x)/(N-1),(cm_y)/(N-1)};
}

velocity cohesion(double c, position CM, boid b){
    return {c*(vector_distance(CM, b.xb).x), c*(vector_distance(CM, b.xb).y)};
}

int main(){
    int N;
    std::cout << "How many boids do you want?/n";
    std::cin >> N;
}
