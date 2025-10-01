#include "masterControl.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iterator>
#include <ostream>
#include "button.cpp"
MasterControl::MasterControl(sf::RenderWindow &window)
{
    clearWindow(window);
}

MasterControl::~MasterControl()
{

}

void MasterControl::initialiseGame(sf::RenderWindow &window)
{
    m_masterCar = new MasterCar(sf::Vector2f(window.getSize().x, window.getSize().y));
    m_road = new Road(sf::Vector2f(window.getSize().x, window.getSize().y));
}
void MasterControl::deleteRoadAndCar(sf::RenderWindow &window)
{
    delete m_masterCar;
    delete m_road;
    m_masterCar = nullptr;
    m_road = nullptr; 
    window.display();
}
void MasterControl::clearWindow(sf::RenderWindow &window, bool toShow)
{
    
    m_masterButton = new Button("StartButton");
    // sf::RectangleShape popUpStartExit(sf::Vector2f(window.getSize().x, window.getSize().y));
    // // popUpStartExit.setSize(sf::Vector2f(500.0f, 400.0f));
    // popUpStartExit.setFillColor(sf::Color::Transparent);
    // popUpStartExit.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    // popUpStartExit.setPosition(0 , 0);
    // sf::Font font;
    // if(!font.loadFromFile("/home/nikhil/devel/vsCode/BuildGame/src/fonts/happy-swirly-font/HappySwirly-KVB7l.ttf")){
    //     std::cout << " Font Not Found";
    // }
    // sf::Text startGameTxt;
    // startGameTxt.setFont(font);
    // startGameTxt.setString("Start Game");
    // startGameTxt.setCharacterSize(40);
    // startGameTxt.setFillColor(sf::Color::Magenta);
    // startGameTxt.setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f-100);

    // sf::Text exitGameTxt;
    // exitGameTxt.setFont(font);
    // exitGameTxt.setString("Exit Game");
    // exitGameTxt.setCharacterSize(40);
    // exitGameTxt.setFillColor(sf::Color::Magenta);
    // exitGameTxt.setPosition(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f);

    // std::cout << "Drawing Pop Up"<< startGameTxt.getString()[0] << std::endl;
    // // window.clear();
    // window.draw(popUpStartExit);
    // window.draw(startGameTxt);
    // window.draw(exitGameTxt);
    m_masterButton->setButtonPositions(window);
    window.draw(m_masterButton->getStartButton());
    window.draw(m_masterButton->getStopButton());
    window.display();
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
    std::cout << " Drawring the start and Stop Game" << std::endl;
    window.clear();
    window.draw(startButton);
}

void MasterControl::showDialog(sf::RenderWindow &window)
{
    startAndExitGame(window);
}

void MasterControl::updateGameStatus(sf::RenderWindow &window, float deltaTime)
{
    if(m_masterCar == nullptr || m_road == nullptr)return;

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
    if(m_masterCar == nullptr || m_road == nullptr)return;
    m_road->draw(window);
    m_masterCar->draw(window);
}

std::string MasterControl::checkClick(sf::Vector2i &mousePos)
{
    std::cout << " Checking" << std::endl;
    sf::Vector2f mF = static_cast<sf::Vector2f>(mousePos);
    std::pair<bool, std::string> result =  m_masterButton->checkClick(mF);

    if(result.first)
    {
        if(result.second == "startGame")
            return "start";
        if(result.second == "stopGame")
            return "stop";
    }

    return "";
}