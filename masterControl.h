#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "masterCar.cpp"
#include "road.cpp"

class MasterControl
{
    public:
    explicit MasterControl(sf::RenderWindow &window);
    ~MasterControl();
    void initialiseGame(sf::RenderWindow &window);
    void deleteRoadAndCar(sf::RenderWindow &window);
    void clearWindow(sf::RenderWindow &window, bool toShow = false);
    void startAndExitGame(sf::RenderWindow &window);
    void showDialog(sf::RenderWindow &window);
    void updateGameStatus(sf::RenderWindow &window, float deltaTime);
    void draw(sf::RenderWindow& window);

    private:
    MasterCar *m_masterCar = nullptr;
    Road *m_road = nullptr;

    sf::Vector2f m_masterWindow;
    public:
    bool m_isGameOver = true;
};