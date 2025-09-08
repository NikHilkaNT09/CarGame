#include "masterControl.h"
#include <SFML/Graphics/Drawable.hpp>

MasterControl::MasterControl(sf::RenderWindow &window)
{

    m_masterCar = new MasterCar(sf::Vector2f(window.getSize().x, window.getSize().y));
    m_road = new Road(sf::Vector2f(window.getSize().x, window.getSize().y));
    this->draw(window);
}

void MasterControl::updateGameStatus(sf::RenderWindow &window, float deltaTime)
{
        m_masterCar->update(deltaTime, window);
        m_road->update(deltaTime, sf::Vector2f(window.getSize().x, window.getSize().y));
        for(auto a:m_road->getObsPostion()){
            std::cout << "$$ "<< a.x << " % " << m_masterCar->getPosition().x << std::endl;

            if(500 - a.y <=50){
            if(m_masterCar->getPosition().x > a.x && m_masterCar->getPosition().x - a.x < 8){
                m_isGameOver = true;
            }
            if(std::abs(a.x- m_masterCar->getPosition().x) <= 90  /*&& std::abs(a.y- m_masterCar->getPosition().y) <=70*/){
                // std::cout << "  " << a.x << " = " << m_masterCar->getPosition().x << " : "<< a.x- m_masterCar->getPosition().x << "  //  "<< a.y << " = "<< m_masterCar->getPosition().y << " : " << a.y- m_masterCar->getPosition().y << std::endl;
            
                m_isGameOver = true;
            }
            }



        }
}

void MasterControl::draw(sf::RenderWindow& window)
{
    
    m_road->draw(window);
    m_masterCar->draw(window);
}