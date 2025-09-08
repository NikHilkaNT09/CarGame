#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glu.h>  
// #include "masterCar.h"
#include "masterCar.cpp"
#include "road.cpp"
using namespace std;
using namespace sf;

bool m_isGameOver = false;

int main(){
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Infinite Road 2D Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // --- Colors ---
    sf::Color backgroundColor(100, 150, 255); // Sky blue

    // Create instances of the Car and Road classes
    MasterCar myCar(sf::Vector2f(window.getSize().x, window.getSize().y));
    Road myRoad(sf::Vector2f(window.getSize().x, window.getSize().y));

    // --- Game Clock for Time-Based Movement ---
    sf::Clock clock;

    // --- Main Game Loop ---
    while (window.isOpen())
    {
        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // --- Event Handling ---
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Update ---
        myCar.update(deltaTime, window);
        myRoad.update(deltaTime, sf::Vector2f(window.getSize().x, window.getSize().y));

        for(auto a:myRoad.getObsPostion()){
            std::cout << " ++++++++++++++  " << a.x << " = " << myCar.getPosition().x<<  std::endl;
            if(std::abs(a.x- myCar.getPosition().x) <= 50 && std::abs(a.y- myCar.getPosition().y) <=50){
                m_isGameOver = true;
            }
        }
        // --- Render ---
        if(!m_isGameOver)
        {
            window.clear(backgroundColor);
            myRoad.draw(window);
            myCar.draw(window);
            window.display();
        }

    }

    return 1;
}
