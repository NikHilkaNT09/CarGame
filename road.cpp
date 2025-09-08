#include "road.h"


    //Constructor
    
Road::Road(const sf::Vector2f& windowSize) {
// Road setup
    m_road.setSize(sf::Vector2f(windowSize.x / 2.0f, windowSize.y));
    m_road.setFillColor(sf::Color(40, 40, 40));
    m_road.setPosition(windowSize.x / 4.0f, 0);

    // Road stripes setup
    const int numStripes = 10;
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
        for (auto& stripe : m_roadStripes)
        {
            stripe.move(0, m_roadSpeed * deltaTime);

            // Reset the stripe to the top if it goes off-screen
            if (stripe.getPosition().y > windowSize.y)
            {
                stripe.setPosition(stripe.getPosition().x, -stripe.getSize().y - (stripe.getSize().y + 100.0f) * 0.5f);
            }
        }
    }

    // Public method to draw the road and its stripes
    void Road::draw(sf::RenderWindow& window) {
        window.draw(m_road);
        for (const auto& stripe : m_roadStripes)
        {
            window.draw(stripe);
        }
    }
