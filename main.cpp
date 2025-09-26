#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glu.h>  
#include <iterator>
#include <ostream>
#include <sys/types.h>
// #include "masterCar.h"
// #include "masterCar.cpp"
// #include "road.cpp"
#include "masterControl.cpp"
using namespace std;
using namespace sf;

// bool g_isGameOver = false;
uint g_score = 0;
bool checkGameOver(){

    // if()
    return true;
}

int main(){
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Infinite Road 2D Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // --- Colors ---
    sf::Color backgroundColor(100, 150, 255); // Sky blue

    // Create instances of the Car and Road classes
    // MasterCar myCar(sf::Vector2f(window.getSize().x, window.getSize().y));
    // Road myRoad(sf::Vector2f(window.getSize().x, window.getSize().y));
    MasterControl *cont = new MasterControl(window);

    // --- Game Clock for Time-Based Movement ---
    sf::Clock clock;
        int event1;
gameInitialisation:
    if(g_score){
        g_score =0;
        std::cout << " Starting the Game" << std::endl;
        cont->startAndExitGame(window);

        event1 = 1;
    }

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

            if(event.type ==sf::Event::MouseButtonPressed){
                cont->m_isGameOver = false;
                event1 = 0;    
            }
                
        }
        
        if(event1==0)cont->updateGameStatus(window, deltaTime);
        

        // --- Render ---
        if(!cont->m_isGameOver)
        {
            g_score++;
            window.clear(backgroundColor);
            cont->draw(window);
            window.display();
        }
        else{
            std::cout << " Game Over" << g_score << std::endl; 
            goto gameInitialisation;
        }

    }

    return 1;
}
