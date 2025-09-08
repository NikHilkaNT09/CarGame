#include "iostream"
#include "obstacle.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Road{
    sf::RectangleShape m_road;
    std::vector<sf::RectangleShape> m_roadStripes;
    std::vector<Obstacle> m_obstacles;
    float m_roadSpeed = 200.0f;
    float m_obstacleSpawnTimer = 0.0f;
public:
    explicit Road(const sf::Vector2f& windowSize);
    void update(float deltaTime, const sf::Vector2f& windowSize); 
    void draw(sf::RenderWindow& window);
    std::vector<sf::Vector2f> getObsPostion();

    //properties:
    //length
    //lanes
    //obstacles
    //
private:
    
};