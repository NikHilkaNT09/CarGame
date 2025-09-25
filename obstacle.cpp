# include "obstacle.h"
#include <SFML/Graphics/Rect.hpp>

Obstacle::Obstacle(float roadLeft, float roadWidth)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0f, 1.0f);

    // Randomly decide if it's a car (rectangle) or a stone (circle)
    bool isCar = (dist(gen) > 0.5f);
    float randomSize = dist(gen) * 20.0f + 50.0f; // Size between 50 and 70

    if (isCar) {
        // Create a car (rectangle)
        sf::RectangleShape* car = new sf::RectangleShape(sf::Vector2f(randomSize, randomSize /** 1.5f*/));
        car->setFillColor(sf::Color(dist(gen) * 255, dist(gen) * 255, dist(gen) * 255)); // Random color
        setCarObstacleImg(car);
        m_shape = car;
    } else {
        // Create a stone (circle)
        sf::CircleShape* stone = new sf::CircleShape(randomSize / 2.0f);
        stone->setFillColor(sf::Color(100, 100, 100)); // Grey color
        setBoulderImg(stone);
        m_shape = stone;
    }

    // Set a random horizontal position on the road
    float xPos = roadLeft + dist(gen) * (roadWidth - m_shape->getGlobalBounds().width);
    m_shape->setPosition(xPos, -200.0f);
}

void Obstacle::setBoulderImg(sf::CircleShape *shape){
    sf::Texture *texture = new sf::Texture();
    texture->setSmooth(true);
    texture->setRepeated(true);
    sf::IntRect(shape->getGlobalBounds());
    if(!texture->loadFromFile("img/old-rock-stone-flat-illustration-icon-vector.jpg")){
        std::cout << "failed To Load Image";
    }

    shape->setTexture(texture);
}

void Obstacle::setCarObstacleImg(sf::RectangleShape *shape){
        sf::Texture *texture = new sf::Texture();
    texture->setSmooth(true);
    texture->setRepeated(true);
    sf::IntRect(shape->getGlobalBounds());
    if(!texture->loadFromFile("img/oie_akM8dBGiINLW.png")){
        std::cout << "failed To Load Image";
    }

    shape->setTexture(texture);
}

void Obstacle::update(float deltaTime, float roadSpeed)
{
    if (m_shape) {
        m_shape->move(0, roadSpeed * deltaTime);
    }
}
void Obstacle::draw(sf::RenderWindow& window)
{
    if (m_shape) {
        window.draw(*m_shape);
    }
}
sf::FloatRect Obstacle::getBounds() const
{
    if (m_shape) {
        return m_shape->getGlobalBounds();
    }
    return sf::FloatRect();
}

sf::Vector2f Obstacle::getPostion()
{
    return m_shape->getPosition();
}