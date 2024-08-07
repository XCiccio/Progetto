#include "sfml_flockof.hpp"

std::vector<sf::CircleShape> create_shapes(std::vector<boid> const& v)
{
  std::vector<sf::CircleShape> shapes;
  for (auto& boid : v) {
    auto circle = sf::CircleShape(5.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(static_cast<float>(boid.pb.x),
                       static_cast<float>(boid.pb.y));
    shapes.push_back(std::move(circle));
  }
  return shapes;
}

void update_window(sf::RenderWindow& window,
                   std::vector<sf::CircleShape>& shapes,
                   std::vector<boid> const& v, float const min_position,
                   float const max_position)
{
  long unsigned int i{0};

  for (auto& shape : shapes) {
    shape.move(static_cast<float>(v[i].pb.x) - shape.getPosition().x,
               static_cast<float>(v[i].pb.y) - shape.getPosition().y);
    i++;
  }

  window.clear(sf::Color::Black);

  for (auto const& shape : shapes) {
    window.draw(shape);
  }
  sf::VertexArray lines(sf::Lines, 8);
  lines[0].position = sf::Vector2f(min_position, min_position);
  lines[0].color    = sf::Color::Red;
  lines[1].position = sf::Vector2f(min_position, max_position);
  lines[1].color    = sf::Color::Red;
  lines[2].position = sf::Vector2f(min_position, min_position);
  lines[2].color    = sf::Color::Red;
  lines[3].position = sf::Vector2f(max_position, min_position);
  lines[3].color    = sf::Color::Red;
  lines[4].position = sf::Vector2f(min_position, max_position);
  lines[4].color    = sf::Color::Red;
  lines[5].position = sf::Vector2f(max_position, max_position);
  lines[5].color    = sf::Color::Red;
  lines[6].position = sf::Vector2f(max_position, min_position);
  lines[6].color    = sf::Color::Red;
  lines[7].position = sf::Vector2f(max_position, max_position);
  lines[7].color    = sf::Color::Red;
  window.draw(lines);
  window.display();
}
