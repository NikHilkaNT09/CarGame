#include "masterCar.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <iterator>
#include <ostream>

namespace {
    const sf::Color CAR_COLOR(255, 0, 0);
    // constexpr char CAR_SIZE
}

using namespace sf;
MasterCar::MasterCar(const sf::Vector2f& windowSize){
    m_body = new RectangleShape();
    m_body->setSize(sf::Vector2f(120.0f, 80.0f));
    m_body->setFillColor(sf::Color(255, 0, 0)); // Red
    m_body->setOrigin(m_body->getSize().x / 2, m_body->getSize().y / 2);
    m_body->setPosition(windowSize.x / 2.0f, windowSize.y - 100.0f);
    m_body->setRotation(90.0f);

    // // Front wheel setup left
    // m_frontWheel[0].setRadius(10.0f);
    // m_frontWheel[0].setFillColor(sf::Color(25, 25, 25)); // Dark gray
    // m_frontWheel[0].setOrigin(m_frontWheel[0].getRadius(), m_frontWheel[0].getRadius());
    // m_frontWheel[0].setPosition(m_body->getPosition().x - 45.0f, m_body->getPosition().y - 45.0f);
    // // m_frontWheel.setRotation(0.0f);
    
    // m_frontWheel[1].setRadius(10.0f);
    // m_frontWheel[1].setFillColor(sf::Color(25, 25, 25)); // Dark gray
    // m_frontWheel[1].setOrigin(m_frontWheel[1].getRadius(), m_frontWheel[1].getRadius());
    // m_frontWheel[1].setPosition(m_body->getPosition().x + 45.0f, m_body->getPosition().y- 45.0f);
    // // m_frontWheel.setRotation(90.0f);

    // // // Back wheel setup
    // m_backWheel[0].setRadius(10.0f);
    // m_backWheel[0].setFillColor(sf::Color(25, 25, 25)); // Dark gray
    // m_backWheel[0].setOrigin(m_backWheel[0].getRadius(), m_backWheel[0].getRadius());
    // m_backWheel[0].setPosition(m_body->getPosition().x - 45.0f, m_body->getPosition().y + 45.0f);
    // // m_backWheel.setRotation(90.0f);

    // m_backWheel[1].setRadius(10.0f);
    // m_backWheel[1].setFillColor(sf::Color(25, 25, 25)); // Dark gray
    // m_backWheel[1].setOrigin(m_backWheel[1].getRadius(), m_backWheel[1].getRadius());
    // m_backWheel[1].setPosition(m_body->getPosition().x + 45.0f, m_body->getPosition().y + 45.0f);
    setCarImage();
}

void MasterCar::setCarImage(){
    sf::Texture *texture = new Texture();
    texture->setSmooth(true);
    texture->setRepeated(true);
    sf::IntRect(m_body->getGlobalBounds());
    if(!texture->loadFromFile("img/img_car.png")){
        std::cout << m_sTag << "failed To Load Image";
    }

    m_body->setTexture(texture);
}
sf::FloatRect MasterCar::getBounds()
{
    return m_body->getGlobalBounds();
}
void MasterCar::update(float deltaTime, sf::RenderWindow& window) {
    float movement = 0.0f;
    
    limitHorizontalMovement(window);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        
        if(!m_isLeftBlocked){
            movement = -m_speed * deltaTime;
        }
       
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        
        if(!m_isRightBlocked){
            movement = m_speed * deltaTime;
        }
    }

    // m_speed *= 0.2;

    // Apply movement to all parts of the car
    m_body->move(movement, 0.0f);
    m_frontWheel[0].move(movement, 0.0f);
    m_backWheel[0].move(movement, 0.0f);
    m_frontWheel[1].move(movement, 0.0f);
    m_backWheel[1].move(movement, 0.0f);
}

void MasterCar::draw(sf::RenderWindow& window) {
    window.draw(*m_body);
    window.draw(m_frontWheel[0]);
    window.draw(m_frontWheel[1]);
    window.draw(m_backWheel[0]);
    window.draw(m_backWheel[1]);
}

bool MasterCar::limitHorizontalMovement(sf::RenderWindow& window){
    static int x = 1;
    // float tm = clock.restart().asSeconds();
    // std::cout << "Entered\t" << tm;
            auto now = std::chrono::system_clock::now();
        // Convert the time point to a time_t object
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        // Use localtime to get a struct tm for formatting
        std::tm* localTime = std::localtime(&currentTime);

        char buffer[80];
        // Format the time as a string with only hours, minutes, and seconds
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S:%Z", localTime);
        
        // Print the formatted time to the console 
        // std::cout << "Current Time: " << buffer << "\t" <<x++ <<"\t" << m_body->getPosition().x <<" ~" << window.getSize().x <<std::endl;
        // std::cout << m_sTag << m_body->getPosition().x << std::endl; 


        (m_body->getPosition().x <= window.getSize().x/4.0f + 50.0f) ? m_isLeftBlocked = true : m_isLeftBlocked = false;
        (m_body->getPosition().x >= window.getSize().x*(3.0f/4) - 50.0f) ? m_isRightBlocked = true : m_isRightBlocked = false;

    return false;
}

 sf::Vector2f MasterCar::getPosition() const
 {
    // std::cout <<  ")))))))" << m_body->getPosition().x << std::endl;
    return m_body->getPosition();
 }