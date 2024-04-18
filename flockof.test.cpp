#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "flockof.hpp"
#include "doctest.h"

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
