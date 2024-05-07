#include "flockof.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

std::vector<sf::CircleShape> create_shapes(std::vector<boid> const&);

int main()

{
  std::cout << "How many boids do you want to generate? \n";
  int N;
  std::cin >> N;
  std::vector v = boids_generator(N);
  std::cout << "Insert the parameter s for separation \n";
  double s;
  std::cin >> s;
  std::cout << "Insert the parameter ds for minimum distance between boids \n";
  double ds;
  std::cin >> ds;
  std::cout << "Insert the parameter a for alignment \n";
  double a;
  std::cin >> a;
  std::cout << "Insert the parameter c for cohesion \n";
  double c;
  std::cin >> c;

  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  constexpr int frame_rate{10};
  window.setFramerateLimit(frame_rate);

  auto shapes = create_shapes(v);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    //evolve the scene
    for (auto& shape : shapes) {
      shape.move (5.f, 5.f);
    }

    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw the shapes
    for (auto const& shape : shapes) {
      window.draw(shape);
    }

    // display the window
    window.display();
  }

}

std::vector<sf::CircleShape> create_shapes(std::vector<boid> const& v)
{
  std::vector<sf::CircleShape> shapes;

  for (auto& boid_: v) {
    auto circle = sf::CircleShape(10.f);
    circle.setFillColor(sf::Color(100, 250, 50));
    circle.setPosition(sf::Vector2f{static_cast<float>(boid_.pb.x),
                                     static_cast<float>(boid_.pb.y)});
    shapes.push_back(std::move(circle));
  }

  return shapes;
}
