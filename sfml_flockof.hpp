#ifndef SFML_FLOCKOF_HPP
#define SFML_FLOCKOF_HPP
#include "flockof.hpp"
#include <SFML/Graphics.hpp>

std::vector<sf::CircleShape> create_shapes(std::vector<boid> const&);

void update_window(sf::RenderWindow&, std::vector<sf::CircleShape>&,
                   std::vector<boid> const&, float const min_position,
                   float const max_position);

#endif
