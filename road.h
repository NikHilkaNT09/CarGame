#include "iostream"
#include <SFML/Graphics.hpp>
#include <vector>

class Road{
    sf::RectangleShape m_road;
    std::vector<sf::RectangleShape> m_roadStripes;
    float m_roadSpeed = 200.0f;
public:
    explicit Road(const sf::Vector2f& windowSize);
    void update(float deltaTime, const sf::Vector2f& windowSize); 
    void draw(sf::RenderWindow& window);

    //properties:
    //length
    //lanes
    //obstacles
    //
private:
    
};