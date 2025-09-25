#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <random>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>

class Obstacle {
public:
    // Constructor to create a random obstacle
    explicit Obstacle(float roadLeft = 0, float roadWidth = 0);

    // Destructor to clean up the dynamically allocated shape
    // ~Obstacle();

    // Prevent copy and move to ensure proper memory management
    // Obstacle(const Obstacle&) = delete;
    // Obstacle& operator=(const Obstacle&) = delete;
    // Obstacle(Obstacle&& other) noexcept;
    // Obstacle& operator=(Obstacle&& other) noexcept;

    // Public methods
    void update(float deltaTime, float roadSpeed);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPostion();
    sf::FloatRect getBounds() const;

private:
    sf::Shape* m_shape;

    void setBoulderImg(sf::CircleShape *shape);
    void setCarObstacleImg(sf::RectangleShape *shape);
};
