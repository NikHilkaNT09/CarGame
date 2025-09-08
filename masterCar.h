#include "iostream"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MasterCar{
public:
    explicit MasterCar(const sf::Vector2f& windowSize);

private:
    sf::RectangleShape *m_body = nullptr;
    sf::CircleShape m_frontWheel[2];
    sf::CircleShape m_backWheel[2];
    float m_speed = 300.0f;
    bool m_isLeftBlocked = false;
    bool m_isRightBlocked = false;

    std::string m_sTag = "MCar: ";

    public:
    void update(float deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool limitHorizontalMovement(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
};