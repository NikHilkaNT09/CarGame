#include "road.h"
#include <SFML/System/Vector2.hpp>

    //Constructor
    
Road::Road(const sf::Vector2f& windowSize) {
// Road setup
    m_road.setSize(sf::Vector2f(windowSize.x / 2.0f, windowSize.y));
    m_road.setFillColor(sf::Color(40, 40, 40));
    m_road.setPosition(windowSize.x / 4.0f, 0);
    
    // Road stripes setup
    const int numStripes = windowSize.y/10;
    float stripeHeight = 50.0f;
    float stripeSpacing = 100.0f;

    for (int i = 0; i < numStripes; ++i)
    {
        sf::RectangleShape stripe(sf::Vector2f(10.0f, stripeHeight));
        stripe.setFillColor(sf::Color(200, 200, 200));
        stripe.setPosition(windowSize.x / 2.0f - stripe.getSize().x / 2.0f, i * stripeSpacing - stripeHeight);
        m_roadStripes.push_back(stripe);
    }
}
void Road::update(float deltaTime, const sf::Vector2f& windowSize) {
    m_roadSpeed > 2000.0f ? m_roadSpeed : m_roadSpeed += 0.5f;
    for (auto& stripe : m_roadStripes)
    {
        stripe.move(0, m_roadSpeed * deltaTime);

        // Reset the stripe to the top if it goes off-screen
        if (stripe.getPosition().y > windowSize.y)
        {
            stripe.setPosition(stripe.getPosition().x, -stripe.getSize().y - (stripe.getSize().y + 100.0f) * 0.5f);
        }
    }

    for (auto& obstacle : m_obstacles) {
        obstacle.update(deltaTime, m_roadSpeed);
    }

    m_obstacles.erase(
        std::remove_if(m_obstacles.begin(), m_obstacles.end(), [&](const Obstacle& obs) {
            return obs.getBounds().top > windowSize.y;
        }),
        m_obstacles.end()
    );

    m_obstacleSpawnTimer += deltaTime;
    if (m_obstacleSpawnTimer > m_limitTimer) { // Spawns a new obstacle every 1.5 seconds
        m_obstacles.emplace_back(m_road.getPosition().x, m_road.getSize().x);
        m_obstacleSpawnTimer = 0.0f;
    }
    
    // m_roadSpeed += m_roadSpeed*0.005;
}

    // Public method to draw the road and its stripes
void Road::draw(sf::RenderWindow& window) {
    window.draw(m_road);
    for (const auto& stripe : m_roadStripes)
    {
        window.draw(stripe);
    }

    for (auto& obstacle : m_obstacles) {
        obstacle.draw(window);
    }
}

std::vector<Obstacle> Road::getObstacles()
{
    return m_obstacles;
}