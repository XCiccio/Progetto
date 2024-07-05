#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "flockof.hpp"
#include "doctest.h"

TEST_CASE("Testing sum p 1")
{
  const position position1{1.0, 2.0};
  const position position2{2.0, 3.0};
  const position sum = position1 + position2;
  CHECK(sum.x == doctest::Approx(3.0));
  CHECK(sum.y == doctest::Approx(5.0));
}

TEST_CASE("Testing sum p 2")
{
  const position position1{50.55, 20.30};
  const position position2{2.22, 3.44};
  const position sum = position1 + position2;
  CHECK(sum.x == doctest::Approx(52.77));
  CHECK(sum.y == doctest::Approx(23.74));
}

TEST_CASE("Testing sum p 3")
{
  const position position1{0.0, 0.0};
  const position position2{0.0, 0.0};
  const position sum = position1 + position2;
  CHECK(sum.x == doctest::Approx(0.0));
  CHECK(sum.y == doctest::Approx(0.0));
}

TEST_CASE("Testing dofference p 1")
{
  const position position1{0.0, 0.0};
  const position position2{20.0, 30.22};
  const position difference = position1 - position2;
  CHECK(difference.x == doctest::Approx(-20.0));
  CHECK(difference.y == doctest::Approx(-30.22));
}

TEST_CASE("Testing difference p 2")
{
  const position position1{50.0, 80.0};
  const position position2{20.0, 100.0};
  const position difference = position1 - position2;
  CHECK(difference.x == doctest::Approx(30.0));
  CHECK(difference.y == doctest::Approx(-20.0));
}

TEST_CASE("Testing / 1")
{
  const position position1{50.0, 30.20};
  const int n            = 5;
  const position resoult = position1 / n;
  CHECK(resoult.x == doctest::Approx(10.0));
  CHECK(resoult.y == doctest::Approx(6.04));
}

TEST_CASE("Testing / 2")
{
  const position position1{20.10, 30.20};
  const int n            = 1;
  const position resoult = position1 / n;
  CHECK(resoult.x == doctest::Approx(20.10));
  CHECK(resoult.y == doctest::Approx(30.20));
}

TEST_CASE("Testing / 3")
{
  const position position1{0.0, 0.0};
  const int n            = 100;
  const position resoult = position1 / n;
  CHECK(resoult.x == doctest::Approx(0.0));
  CHECK(resoult.y == doctest::Approx(0.0));
}

TEST_CASE("Testing * p 1")
{
  const position position1{50.0, 30.20};
  double d               = 5.0;
  const position resoult = position1 * d;
  CHECK(resoult.x == doctest::Approx(250.0));
  CHECK(resoult.y == doctest::Approx(151.0));
}

TEST_CASE("Testing sum v 1")
{
  const velocity velocity1{1.0, 2.0};
  const velocity velocity2{2.0, 3.0};
  const velocity sum = velocity1 + velocity2;
  CHECK(sum.v_x == doctest::Approx(3.0));
  CHECK(sum.v_y == doctest::Approx(5.0));
}

TEST_CASE("Testing sum v 2")
{
  const velocity velocity1{20.0, 2.0};
  const velocity velocity2{-10.5, -3.0};
  const velocity sum = velocity1 + velocity2;
  CHECK(sum.v_x == doctest::Approx(9.5));
  CHECK(sum.v_y == doctest::Approx(-1.0));
}

TEST_CASE("Testing difference v 1")
{
  const velocity velocity1{20.0, 2.0};
  const velocity velocity2{-10.5, -3.0};
  const velocity difference = velocity1 - velocity2;
  CHECK(difference.v_x == doctest::Approx(30.5));
  CHECK(difference.v_y == doctest::Approx(5.0));
}

TEST_CASE("Testing difference v 2")
{
  const velocity velocity1{50.0, -32.10};
  const velocity velocity2{110.5, -3.15};
  const velocity difference = velocity1 - velocity2;
  CHECK(difference.v_x == doctest::Approx(-60.5));
  CHECK(difference.v_y == doctest::Approx(-28.95));
}

TEST_CASE("Testing difference v 3")
{
  const velocity velocity1{0.0, 0.0};
  const velocity velocity2{0.0, -3.0};
  const velocity difference = velocity1 - velocity2;
  CHECK(difference.v_x == doctest::Approx(0.0));
  CHECK(difference.v_y == doctest::Approx(3.0));
}

TEST_CASE("Testing * v 1")
{
  const velocity velocity1{50.0, 30.20};
  double d               = 5.0;
  const velocity resoult = d * velocity1;
  CHECK(resoult.v_x == doctest::Approx(250.0));
  CHECK(resoult.v_y == doctest::Approx(151.0));
}

TEST_CASE("Testing * v 2")
{
  const velocity velocity1{10.0, -40.50};
  double d               = -2.0;
  const velocity resoult = d * velocity1;
  CHECK(resoult.v_x == doctest::Approx(-20.0));
  CHECK(resoult.v_y == doctest::Approx(81.0));
}

TEST_CASE("Testing * v 3")
{
  const velocity velocity1{0.0, 0.0};
  double d               = -2.0;
  const velocity resoult = d * velocity1;
  CHECK(resoult.v_x == doctest::Approx(0.0));
  CHECK(resoult.v_y == doctest::Approx(0.0));
}

TEST_CASE("Testing * v 4")
{
  const velocity velocity1{10.0, -40.50};
  double d               = 0.0;
  const velocity resoult = d * velocity1;
  CHECK(resoult.v_x == doctest::Approx(0.0));
  CHECK(resoult.v_y == doctest::Approx(0.0));
}

TEST_CASE("Testing * v 5")
{
  const velocity velocity1{0.0, 0.0};
  double d               = 0.0;
  const velocity resoult = d * velocity1;
  CHECK(resoult.v_x == doctest::Approx(0.0));
  CHECK(resoult.v_y == doctest::Approx(0.0));
}

TEST_CASE("Testing distance 1")
{
  const position position1{1.0, 2.0};
  const position position2{2.0, 3.0};
  const double distance_ = distance(position1, position2);
  CHECK(distance_ == doctest::Approx(1.41421));
}

TEST_CASE("Testing distance 2")
{
  const position position1{-1.0, 2.0};
  const position position2{2.0, 3.0};
  const double distance_ = distance(position1, position2);
  CHECK(distance_ == doctest::Approx(3.16227));
}

TEST_CASE("Testing distance 3")
{
  const position position1{0.0, 2.0};
  const position position2{0.0, 3.0};
  const double distance_ = distance(position1, position2);
  CHECK(distance_ == doctest::Approx(1.0));
}

TEST_CASE("Testing the cm 1")
{
  const std::vector<boid> vec{{{2.0, 3.0}, {1.0, 4.0}},
                              {{2.0, 3.0}, {1.0, 4.0}}};
  const int N{2};
  const position cmcheck = cm(vec, N);
  CHECK(cmcheck.x == doctest::Approx(2.0));
  CHECK(cmcheck.y == doctest::Approx(3.0));
}

TEST_CASE("Testing the cm 2")
{
  const std::vector<boid> vec{{{0.0, 0.0}, {1.0, 4.0}},
                              {{0.0, 0.0}, {1.0, 4.0}}};
  const int N{2};
  const position cmcheck = cm(vec, N);
  CHECK(cmcheck.x == doctest::Approx(0.0));
  CHECK(cmcheck.y == doctest::Approx(0.0));
}

TEST_CASE("Testing new cohesion 1")
{
  const std::vector<boid> v{{{50., 100.}, {10., 10.}},
                            {{55., 105.}, {-12., 11.}},
                            {{45., 95.}, {7., -8.}}};
  double const c{0.3};
  double const d{50.};
  auto cohesion1 = cohesion(v, v[0], d, c, 2);
  auto cohesion2 = cohesion(v, v[1], d, c, 2);
  auto cohesion3 = cohesion(v, v[2], d, c, 2);
  CHECK(cohesion1.v_x == doctest::Approx(0));
  CHECK(cohesion1.v_y == doctest::Approx(0));
  CHECK(cohesion2.v_x == doctest::Approx(-2.25));
  CHECK(cohesion2.v_y == doctest::Approx(-2.25));
  CHECK(cohesion3.v_x == doctest::Approx(2.25));
  CHECK(cohesion3.v_y == doctest::Approx(2.25));
}

TEST_CASE("Testing new cohesion 2")
{
  const std::vector<boid> v{{{788, 302.}, {10., 10.}},
                            {{760., 298.}, {-12., 11.}},
                            {{775., 310.}, {7., -8.}}};
  double const c = 0.1;
  double const d = 50.;
  auto cohesion1 = cohesion(v, v[0], d, c, 2);
  auto cohesion2 = cohesion(v, v[1], d, c, 2);
  auto cohesion3 = cohesion(v, v[2], d, c, 2);
  CHECK(cohesion1.v_x == doctest::Approx(-2.05));
  CHECK(cohesion1.v_y == doctest::Approx(0.2));
  CHECK(cohesion2.v_x == doctest::Approx(2.15));
  CHECK(cohesion2.v_y == doctest::Approx(0.8));
  CHECK(cohesion3.v_x == doctest::Approx(-0.1));
  CHECK(cohesion3.v_y == doctest::Approx(-1));
}

TEST_CASE("Testing alignment 1")
{
  const boid b{{(5.0), (2.0)}, {(1.0), (4.0)}};
  const std::vector<boid> v{{{2.0, 3.0}, {2.0, 1.0}},
                            {{5.0, 2.0}, {1.0, 4.0}},
                            {{2.0, 3.0}, {3.0, 2.0}}};
  const double d{50.};
  const double a{0.5};
  const velocity v2 = alignment(v, b, d, a, 2);
  CHECK(v2.v_x == doctest::Approx(0.75));
  CHECK(v2.v_y == doctest::Approx(-1.25));
}

TEST_CASE("Testing alignment 2")
{
  const boid b{{(5.0), (2.0)}, {(1.0), (2.0)}};
  const std::vector<boid> v{{{2.0, 3.0}, {1.0, 2.0}},
                            {{5.0, 2.0}, {1.0, 2.0}},
                            {{2.0, 3.0}, {1.0, 2.0}}};
  const double a{0.7};
  const double d{25.};
  const velocity v2 = alignment(v, b, d, a, 2);
  CHECK(v2.v_x == doctest::Approx(0.));
  CHECK(v2.v_y == doctest::Approx(0.));
}

TEST_CASE("Testing alignment 3")
{
  const boid b{{(5.0), (2.0)}, {(2.0), (0.0)}};
  const std::vector<boid> v{{{2.0, 3.0}, {2.0, 0.0}},
                            {{5.0, 2.0}, {2.0, 0.0}},
                            {{2.0, 3.0}, {0.0, -2.0}},
                            {{2.0, 3.0}, {2.0, -3.0}}};
  const double a{0.8};
  const double d{5};
  const velocity v2 = alignment(v, b, d, a, 3);
  CHECK(v2.v_x == doctest::Approx(-0.53333));
  CHECK(v2.v_y == doctest::Approx(-1.33333));
}

TEST_CASE("Testing separation 1")
{
  const boid b{{(3.0), (3.0)}, {(2.0), (0.0)}};
  const std::vector<boid> vec{
      {{3.0, 3.0}, {2.0, 0.0}},
      {{4.0, 2.0}, {3.0, 1.0}},
  };
  const double s{1};
  const double ds{1};
  const velocity v3 = separation(vec, b, s, ds);
  CHECK(v3.v_x == doctest::Approx(0.));
  CHECK(v3.v_y == doctest::Approx(0.));
}

TEST_CASE("Testing separation 2")
{
  const boid b{{(3.0), (3.0)}, {(2.0), (0.0)}};
  const std::vector<boid> vec{
      {{3.0, 3.0}, {2.0, 0.0}},
      {{4.0, 2.0}, {3.0, 1.0}},
  };
  const double s{1};
  const double ds{2};
  const velocity v3 = separation(vec, b, s, ds);
  CHECK(v3.v_x == doctest::Approx(-1.0));
  CHECK(v3.v_y == doctest::Approx(1.0));
}

TEST_CASE("Testing separation 3")
{
  const boid b{{(2.0), (0.0)}, {(2.0), (3.0)}};
  const std::vector<boid> vec{{{2.0, 0.0}, {2.0, 3.0}},
                              {{3.0, 1.0}, {7.0, 1.0}},
                              {{0.0, -2.0}, {1.0, -2.0}},
                              {{2.0, -3.0}, {3.0, -3.0}}};
  const double s{0.5};
  const double ds{4};
  const velocity v3 = separation(vec, b, s, ds);
  CHECK(v3.v_x == doctest::Approx(0.5));
  CHECK(v3.v_y == doctest::Approx(2.0));
}

TEST_CASE("Testing separation 4")
{
  const boid b{{(2.0), (0.0)}, {(2.0), (3.0)}};
  const std::vector<boid> vec{{{2.0, 0.0}, {2.0, 3.0}},
                              {{3.0, 1.0}, {7.0, 1.0}},
                              {{0.0, -2.0}, {1.0, -2.0}},
                              {{2.0, -3.0}, {3.0, -3.0}}};
  const double s{1.0};
  const double ds{2.9};
  const velocity v3 = separation(vec, b, s, ds);
  CHECK(v3.v_x == doctest::Approx(1.0));
  CHECK(v3.v_y == doctest::Approx(1.0));
}

TEST_CASE("Testing separation 5")
{
  const boid b{{(2.0), (1.0)}, {(3.0), (0.0)}};
  const std::vector<boid> vec{{{2.0, 1.0}, {3.0, 0.0}},
                              {{2.0, 2.0}, {7.0, 1.0}},
                              {{4.0, 0.0}, {1.0, -2.0}}};
  const double s{1};
  const double ds{1.5};
  const velocity v3 = separation(vec, b, s, ds);
  CHECK(v3.v_x == doctest::Approx(0.0));
  CHECK(v3.v_y == doctest::Approx(-1.0));
}

TEST_CASE("Testing the wall_repulsion function 1")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(800.), (100.)}, {(20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(-20.));
  CHECK(v.v_y == doctest::Approx(20.));
}

TEST_CASE("Testing the wall_repulsion function 2")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(1.), (100.)}, {(-20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(20.));
  CHECK(v.v_y == doctest::Approx(20.));
}

TEST_CASE("Testing the wall_repulsion function 3")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(100.), (800.)}, {(-20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(-20.));
  CHECK(v.v_y == doctest::Approx(-20.));
}

TEST_CASE("Testing the wall_repulsion function 4")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(800.), (800.)}, {(20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(-20.));
  CHECK(v.v_y == doctest::Approx(-20.));
}

TEST_CASE("Testing the wall_repulsion function 5")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(100.), (790.)}, {(-20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(-20.));
  CHECK(v.v_y == doctest::Approx(20.));
}

TEST_CASE("Testing the wall_repulsion function 6")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(790.), (790.)}, {(20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(20.));
  CHECK(v.v_y == doctest::Approx(20.));
}

TEST_CASE("Testing the wall_repulsion function 7")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(100.), (800.)}, {(-20.), (20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(-20.));
  CHECK(v.v_y == doctest::Approx(-20.));
}

TEST_CASE("Testing the wall_repulsion function 8")
{
  const double min_position{10.};
  const double max_position{790.};
  boid b{{(5.), (5.)}, {(-20.), (-20.)}};
  const velocity v = wall_repulsion(b, min_position, max_position);
  CHECK(v.v_x == doctest::Approx(20.));
  CHECK(v.v_y == doctest::Approx(20.));
}

TEST_CASE("Testing update_boids 1")
{
  const double min_position{10.};
  const double max_position{790.};
  const double max_velocity{50.};
  const double frame_rate_limit{1. / 60.};
  const double s  = 0.2;
  const double ds = 15;
  const double d  = 50.;
  const double a  = 0.2;
  const double c  = 0.2;
  std::vector<boid> v{{{450., 320.}, {10., 10.}},
                      {{428., 289.}, {15., 5.}},
                      {{465., 300.}, {5., 8.}}};
  std::vector<boid> vec =
      update_boids(v, s, d, ds, a, c, min_position, max_position, max_velocity,
                   frame_rate_limit);
  CHECK(vec[0].pb.x == doctest::Approx(450.155));
  CHECK(vec[0].pb.y == doctest::Approx(320.07));
  CHECK(vec[0].vb.v_x == doctest::Approx(9.3));
  CHECK(vec[0].vb.v_y == doctest::Approx(4.2));
  CHECK(vec[1].pb.x == doctest::Approx(428.32333));
  CHECK(vec[1].pb.y == doctest::Approx(289.167));
  CHECK(vec[1].vb.v_x == doctest::Approx(19.4));
  CHECK(vec[1].vb.v_y == doctest::Approx(10));
  CHECK(vec[2].pb.x == doctest::Approx(465.022));
  CHECK(vec[2].pb.y == doctest::Approx(300.147));
  CHECK(vec[2].vb.v_x == doctest::Approx(1.3));
  CHECK(vec[2].vb.v_y == doctest::Approx(8.8));
}

TEST_CASE("Testing update_boids 2")
{
  const double min_position{10.};
  const double max_position{790.};
  const double max_velocity{50.};
  const double frame_rate_limit{1. / 60.};
  const double s  = 0.5;
  const double ds = 15;
  const double a  = 0.1;
  const double c  = 0.3;
  const double d  = 50.;
  std::vector<boid> vec{{{50., 100.}, {10., 10.}},
                        {{55., 105.}, {-12., 11.}},
                        {{100., 650.}, {7., -8.}}};
  vec = update_boids(vec, s, d, ds, a, c, min_position, max_position,
                     max_velocity, frame_rate_limit);
  CHECK(vec[0].pb.x == doctest::Approx(50.1133));
  CHECK(vec[0].pb.y == doctest::Approx(100.152));
  CHECK(vec[0].vb.v_x == doctest::Approx(6.8));
  CHECK(vec[0].vb.v_y == doctest::Approx(9.1));
  CHECK(vec[1].pb.x == doctest::Approx(54.8533));
  CHECK(vec[1].pb.y == doctest::Approx(105.198));
  CHECK(vec[1].vb.v_x == doctest::Approx(-8.8));
  CHECK(vec[1].vb.v_y == doctest::Approx(11.9));
  CHECK(vec[2].pb.x == doctest::Approx(100.11666));
  CHECK(vec[2].pb.y == doctest::Approx(649.866667));
  CHECK(vec[2].vb.v_x == doctest::Approx(7.));
  CHECK(vec[2].vb.v_y == doctest::Approx(-8.));
}

TEST_CASE("Testing data analysis 1")
{
  const int N = 4;
  std::vector<boid> v{{{3., 2.}, {5., 2.}},
                      {{11., 2.}, {-3., 4.}},
                      {{3., 8.}, {4., -8.}},
                      {{11., 8.}, {-7., -1.}}};
  data statistiche_posizione = position_data_analysis(v, N);
  const position cmcheck     = cm(v, N);
  data statistiche_velocita  = velocity_data_analysis(v, N);
  CHECK(cmcheck.x == doctest::Approx(7.0));
  CHECK(cmcheck.y == doctest::Approx(5.0));
  CHECK(statistiche_posizione.mean == doctest::Approx(5.0));
  CHECK(statistiche_posizione.sigma == doctest::Approx(0.0));
  CHECK(statistiche_velocita.mean == doctest::Approx(6.600126));
  CHECK(statistiche_velocita.sigma == doctest::Approx(1.803084));
}

TEST_CASE("Testing data analysis 2 ")
{
  const int N = 3;
  std::vector<boid> v{
      {{2., 2.}, {5., 2.}},
      {{9., 4.}, {-3., 4.}},
      {{5., 7.}, {4., -8.}},
  };
  data statistiche_posizione = position_data_analysis(v, N);
  const position cmcheck     = cm(v, N);
  CHECK(cmcheck.x == doctest::Approx(5.333333));
  CHECK(cmcheck.y == doctest::Approx(4.333333));
  CHECK(statistiche_posizione.mean == doctest::Approx(3.479352));
  CHECK(statistiche_posizione.sigma == doctest::Approx(0.712617));
}
