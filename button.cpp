#include "button.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "img/startGameImg.h"
#include "img/exitGameImg.h"
// #include <SFML/Graphics/CircleShape.hpp>
// #include <SFML/Graphics/Color.hpp>
// #include <SFML/Graphics/ConvexShape.hpp>
// #include <SFML/Graphics/RectangleShape.hpp>
// #include <SFML/Graphics/RenderWindow.hpp>
// #include <SFML/Graphics/Shape.hpp>
// #include <SFML/System/Vector2.hpp>
Button::Button(std::string text){
    m_startButton = new sf::RectangleShape(sf::Vector2f(150,50));
    m_stopButton = new sf::RectangleShape(sf::Vector2f(150,50));
    sf::Text startTxt;
    // m_masterButton->setPosition()
}

Button::~Button()
{
    delete m_startButton;
    delete m_stopButton;
    m_startButton = nullptr;
    m_startButton = nullptr;
}
void Button::setButtonPositions(sf::RenderWindow &window)
{
    sf::Texture *txtStart = new sf::Texture();
    sf::Texture *txtStop = new sf::Texture();;
    if(!txtStart->loadFromMemory(start_game_png, start_game_png_len))
    {
        std::cout << "Failed to Load Start Game Image";
    }
    if(!txtStop->loadFromMemory(exit_game_png, exit_game_png_len)){}
    {
        std::cout << "Failed to Load Start Game Image";
    }
    // txtStart.
    // txtStart.loadFromImage(const Image &image);

    m_startButton->setFillColor(sf::Color::Green);
    m_startButton->setTexture(txtStart);
    m_startButton->setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f-100);

    m_stopButton->setFillColor(sf::Color::Red);
    m_stopButton->setTexture(txtStop);
    m_stopButton->setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f);
    // m_startButton->set
}
std::pair<bool, std::string> Button::checkClick(sf::Vector2f &mousePos)
{
    // std::cout << " Root Checking x  " << mousePos.x << ":" << m_stopButton->getPosition().x <<", "  << std::endl;
    //    std::cout << " Root Checking y  " << mousePos.y << ":" << m_stopButton->getPosition().y <<", "   << std::endl;
    //    std::cout << "  %% " << mousePos.y << ": " << m_stopButton->getPosition().y;
    if(mousePos.x  > m_startButton->getPosition().x -75 && mousePos.x  < m_startButton->getPosition().x + 150
        && mousePos.y >= m_startButton->getPosition().y  && mousePos.y <= m_startButton->getPosition().y +50)
    {
        return {true, "startGame"};
    }

    if(mousePos.x  > m_stopButton->getPosition().x - 75 && mousePos.x  < m_stopButton->getPosition().x + 150
        && mousePos.y >= m_stopButton->getPosition().y && mousePos.y <= m_stopButton->getPosition().y + 50)
    {
        std::cout << " Stopping Game !! " << std::endl;
        return {true, "stopGame"};
    }

    return {false, ""};
}

sf::RectangleShape Button::getStartButton() const
{
    return *m_startButton;
}

sf::RectangleShape Button::getStopButton() const
{
    return *m_stopButton;
}