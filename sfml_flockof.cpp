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
                   std::vector<boid> const& v)
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

  window.display();
}
