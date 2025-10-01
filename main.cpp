#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
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

bool g_bStartScreen = true;
bool g_isGameRunning = false;
// bool g_bStartScreen = false;
uint g_score = 0;
bool checkGameOver(){

    // if()
    return true;
}

void showMainScreen(sf::RenderWindow &window){
    sf::RenderWindow popUpStartExit(sf::VideoMode(300, 200), "Start and Exit");
    sf::Font font;
    if(!font.loadFromFile("/home/nikhil/devel/vsCode/BuildGame/src/fonts/happy-swirly-font.zip")){
        std::cout << " Font Not Found";
    }
    sf::Text popupText;
    popupText.setFont(font);
    popupText.setString("Start Game");
    popupText.setCharacterSize(30);
    popupText.setFillColor(sf::Color::White);
    popupText.setPosition(0, 0);
}
int main(){
    
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "Infinite Road 2D Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Color backgroundColor(100, 150, 255); // Sky blue

    MasterControl *m_masterCont = new MasterControl(window);
    bool showPopup = false;

    // --- Game Clock for Time-Based Movement ---
    sf::Clock clock;
    int event1;
    bool retry = true;

    sf::Font font;
    sf::Text scoreCard;
    scoreCard.setPosition(10, 10);
    scoreCard.setFont(font);
    scoreCard.setCharacterSize(24);
    scoreCard.setFillColor(sf::Color::Black);
    scoreCard.setString("Score: " + std::to_string(g_score));  
gameInitialisation:
    if(g_score){
        g_score =0;
        std::cout << " Starting the Game" << std::endl;
        // cont->startAndExitGame(window);
        
        event1 = 1;
    }

    // --- Main Game Loop ---
    while (window.isOpen())
    {

        if(g_bStartScreen){
            m_masterCont->clearWindow(window);
            g_bStartScreen = false;
        }
        // Get the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();


        // --- Event Handling ---
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)  
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                std::string res = m_masterCont->checkClick(pos);
                if(res == "start"){
                    std::cout << "Starting";
                    m_masterCont->initialiseGame(window);
                    m_masterCont->m_isGameOver = false;
                    g_bStartScreen=false;
                    g_isGameRunning = true;
                    event1 = 0;    
                }

                if(res == "stop"){
                    return -1;
                }
            }  
            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                // m_masterCont->initialiseGame(window);
                // m_masterCont->m_isGameOver = false;
                // g_bStartScreen=false;
                // g_isGameRunning = true;
                // // retry = true;
                // event1 = 0;    
                 // Toggle pop-up visibility
            // }
      
        }
        // cont->startAndExitGame(window);
        // if(event1==0 && !m_masterCont->m_isGameOver)m_masterCont->updateGameStatus(window, deltaTime);
        
        // --- Render ---
        if(!m_masterCont->m_isGameOver)
        {
            m_masterCont->updateGameStatus(window, deltaTime);
            g_score++;
            window.clear(backgroundColor);
            m_masterCont->draw(window);
            window.draw(scoreCard);
            window.display();
        }
        else if(g_isGameRunning ){
            g_isGameRunning = false;
            m_masterCont->deleteRoadAndCar(window);
            m_masterCont->clearWindow(window);
        }
        // else if(!g_bStartScreen){
        //     g_bStartScreen = true;
        //         // std::cout << " Game Over" << g_score << std::endl; 
        //         // cont->startAndExitGame(window);
        //         // retry = false;
        //         // goto gameInitialisation;


        // }

    }

    return 1;
}
