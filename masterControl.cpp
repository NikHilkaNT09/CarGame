#include "masterControl.h"
#include <SFML/Graphics/Drawable.hpp>
#include <iterator>

MasterControl::MasterControl(sf::RenderWindow &window)
{
    m_masterCar = new MasterCar(sf::Vector2f(window.getSize().x, window.getSize().y));
    m_road = new Road(sf::Vector2f(window.getSize().x, window.getSize().y));
    std::cout<< "  ^^" << m_masterCar->getPosition().x << "  " << m_masterCar->getPosition().y;
}

void MasterControl::startAndExitGame(sf::RenderWindow &window)
{
    sf::Font font;
    sf::RectangleShape startButton(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color(100, 100, 100));
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(2);
    startButton.setPosition((window.getSize().x - startButton.getSize().x) / 2, 300);

    sf::Text startText;
    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    // Center the text on the button
    startText.setPosition(
        startButton.getPosition().x + (startButton.getSize().x - startText.getGlobalBounds().width) / 2,
        startButton.getPosition().y + (startButton.getSize().y - startText.getGlobalBounds().height) / 2 - 5
    );

    // "Exit" button
    sf::RectangleShape exitButton(sf::Vector2f(200.f, 50.f));
    exitButton.setFillColor(sf::Color(100, 100, 100));
    exitButton.setOutlineColor(sf::Color::White);
    exitButton.setOutlineThickness(2);
    exitButton.setPosition((window.getSize().x - exitButton.getSize().x) / 2, 400);

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    // Center the text on the button
    exitText.setPosition(
        exitButton.getPosition().x + (exitButton.getSize().x - exitText.getGlobalBounds().width) / 2,
        exitButton.getPosition().y + (exitButton.getSize().y - exitText.getGlobalBounds().height) / 2 - 5
    );
    
    // Text for the game state
    sf::Text gameText;
    gameText.setFont(font);
    gameText.setString("Game is Running!");
    gameText.setCharacterSize(40);
    gameText.setFillColor(sf::Color::White);
    gameText.setPosition((window.getSize().x - gameText.getGlobalBounds().width) / 2, 200);
}

void MasterControl::showDialog(sf::RenderWindow &window)
{
    startAndExitGame(window);
}

void MasterControl::updateGameStatus(sf::RenderWindow &window, float deltaTime)
{
        m_masterCar->update(deltaTime, window);
        m_road->update(deltaTime, sf::Vector2f(window.getSize().x, window.getSize().y));
        for(auto a:m_road->getObstacles()){

            if(m_masterCar->getBounds().intersects(a.getBounds())){
                m_isGameOver = true;
            }
        }
}

void MasterControl::draw(sf::RenderWindow& window)
{
    
    m_road->draw(window);
    m_masterCar->draw(window);
}