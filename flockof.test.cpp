#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "flockof.hpp"
#include "doctest.h"

TEST_CASE("Testing distance 1")
{
  const position position1{2.0, 0.0};
  const position position2{0.0, -2.0};
  const double distance_ = distance(position1, position2);
  CHECK(distance_ == doctest::Approx(2.82842712));
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

TEST_CASE("Testing vector distance 1")
{
  const position position1{0.0, 0.0};
  const position position2{0.0, 0.0};
  const position vectordistance_ = vector_distance(position1, position2);
  CHECK(vectordistance_.x == doctest::Approx(0.0));
  CHECK(vectordistance_.y == doctest::Approx(0.0));
}

TEST_CASE("Testing vector distance 2")
{
  const position position1{1.0, 2.0};
  const position position2{-5.0, 3.0};
  const position vectordistance_ = vector_distance(position1, position2);
  CHECK(vectordistance_.x == doctest::Approx(6.0));
  CHECK(vectordistance_.y == doctest::Approx(-1.0));
}

TEST_CASE("Testing sum of velocity 1")
{
  const velocity v1{1.0, 2.0};
  const velocity v2{4.0, 0.0};
  const velocity vcheck_ = sum_of_velocity(v1, v2);
  CHECK(vcheck_.v_x == doctest::Approx(5.0));
  CHECK(vcheck_.v_y == doctest::Approx(2.0));
}

TEST_CASE("Testing sum of velocity 2")
{
  const velocity v1{1.0, 2.0};
  const velocity v2{-1.0, -2.0};
  const velocity vcheck_ = sum_of_velocity(v1, v2);
  CHECK(vcheck_.v_x == doctest::Approx(0.0));
  CHECK(vcheck_.v_y == doctest::Approx(0.0));
}

TEST_CASE("Testing the cm 1")
{
  const std::vector<boid> vec{{{2.0, 3.0}, {1.0, 4.0}},
                              {{2.0, 3.0}, {1.0, 4.0}}};
  const int N{2};
  const position cmcheck = cm(vec, N);
  CHECK(cmcheck.x == doctest::Approx(4.0));
  CHECK(cmcheck.y == doctest::Approx(6.0));
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

TEST_CASE("Testing the cohesion 1")
{
  const boid b{{(1.0), (4.0)}, {(1.0), (4.0)}};
  const double c{0.5};
  const position CM{-3.0, -2.0};
  const velocity v1 = cohesion(c, CM, b);
  CHECK(v1.v_x == doctest::Approx(-2.0));
  CHECK(v1.v_y == doctest::Approx(-3.0));
}

TEST_CASE("Testing the cohesion 2")
{
  const boid b{{(5.0), (2.0)}, {(1.0), (4.0)}};
  const double c{0.5};
  const position CM{5.0, 2.0};
  const velocity v1 = cohesion(c, CM, b);
  CHECK(v1.v_x == doctest::Approx(0.0));
  CHECK(v1.v_y == doctest::Approx(0.0));
}

TEST_CASE("Testing alignment 1")
{
  const boid b{{(5.0), (2.0)}, {(1.0), (4.0)}};
  const std::vector<boid> vec{{{2.0, 3.0}, {2.0, 1.0}},
                              {{5.0, 2.0}, {1.0, 4.0}},
                              {{2.0, 3.0}, {3.0, 2.0}}};
  const int N{3};
  const double a{0.5};
  const velocity v2 = alignment(a, b, vec, N);
  CHECK(v2.v_x == doctest::Approx(0.75));
  CHECK(v2.v_y == doctest::Approx(-1.25));
}

TEST_CASE("Testing alignment 2")
{
  const boid b{{(5.0), (2.0)}, {(1.0), (2.0)}};
  const std::vector<boid> vec{{{2.0, 3.0}, {1.0, 2.0}},
                              {{5.0, 2.0}, {1.0, 2.0}},
                              {{2.0, 3.0}, {1.0, 2.0}}};
  const int N{3};
  const double a{0.7};
  const velocity v2 = alignment(a, b, vec, N);
  CHECK(v2.v_x == doctest::Approx(0.));
  CHECK(v2.v_y == doctest::Approx(0.));
}

TEST_CASE("Testing alignment 3")
{
  const boid b{{(5.0), (2.0)}, {(2.0), (0.0)}};
  const std::vector<boid> vec{{{2.0, 3.0}, {2.0, 0.0}},
                              {{5.0, 2.0}, {3.0, 1.0}},
                              {{2.0, 3.0}, {0.0, -2.0}},
                              {{2.0, 3.0}, {2.0, -3.0}}};
  const int N{4};
  const double a{0.8};
  const velocity v2 = alignment(a, b, vec, N);
  CHECK(v2.v_x == doctest::Approx(-0.266666667));
  CHECK(v2.v_y == doctest::Approx(-1.06666667));
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
  const velocity v3 = separation(s, ds, b, vec);
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
  const velocity v3 = separation(s, ds, b, vec);
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
  const velocity v3 = separation(s, ds, b, vec);
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
  const velocity v3 = separation(s, ds, b, vec);
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
  const velocity v3 = separation(s, ds, b, vec);
  CHECK(v3.v_x == doctest::Approx(0.0));
  CHECK(v3.v_y == doctest::Approx(-1.0));
} 
