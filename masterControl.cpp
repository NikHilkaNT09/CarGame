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
        for(auto a:m_road->getObsPostion()){

            if(500 - a.y <=50){
            // if(m_masterCar->getPosition().x > a.x && m_masterCar->getPosition().x - a.x < 8){

            // std::cout << "$$$ "<< a.x << " % " << m_masterCar->getPosition().x << std::endl;
            //     m_isGameOver = true;
            // }
            // else if(std::abs(a.x- m_masterCar->getPosition().x) <= 12  /*&& std::abs(a.y- m_masterCar->getPosition().y) <=70*/){
            //     // std::cout << "  " << a.x << " = " << m_masterCar->getPosition().x << " : "<< a.x- m_masterCar->getPosition().x << "  //  "<< a.y << " = "<< m_masterCar->getPosition().y << " : " << a.y- m_masterCar->getPosition().y << std::endl;
            
            // std::cout << "###"<< a.x << " % " << m_masterCar->getPosition().x << std::endl;
            //     m_isGameOver = true;
            // }

            auto leftEdge = m_masterCar->getPosition().x - 60;
            auto rightEdge = m_masterCar->getPosition().x + 60;
            auto leftEdgeObs = a.x - 40;
            auto rightEdgeObs = a.x + 40;
            
            std::cout << "@@ "<< leftEdge << " @@ " << rightEdge << " @@ "<< leftEdgeObs << " @@ " << rightEdgeObs << std::endl;

            if(leftEdge < rightEdgeObs && leftEdgeObs < leftEdge){
                std::cout << "#####" << std::endl;
                m_isGameOver = true;
                break;
            }
            if(rightEdge > leftEdgeObs && rightEdge < rightEdgeObs){
                std::cout << "$$$$$" << std::endl;
                m_isGameOver = true;
                break;
            }
//             if(!(leftEdge > leftEdgeObs && leftEdge > rightEdgeObs) || !(rightEdge < leftEdgeObs && rightEdge < rightEdgeObs) ){
// m_isGameOver = true;
//             }
                
//                 else if(){
// m_isGameOver = true;
//                 }
            }
            



        }
}

void MasterControl::draw(sf::RenderWindow& window)
{
    
    m_road->draw(window);
    m_masterCar->draw(window);
}