#include "iostream"
#include <SFML/Graphics.hpp>
#include <vector>

class MasterCar{
public:
    explicit MasterCar(const sf::Vector2f& windowSize);

private:
    sf::RectangleShape *m_body = nullptr;
    sf::CircleShape m_frontWheel[2];
    sf::CircleShape m_backWheel[2];
    float m_speed = 300.0f;
    std::string flag = "";

    public:
    void update(float deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool limitHorizontalMovement(sf::RenderWindow& window, std::string deltaTime);
};