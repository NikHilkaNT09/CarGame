#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "masterCar.cpp"
#include "road.cpp"

class MasterControl
{
    public:
    explicit MasterControl(sf::Vector2f &window);

    private:
    MasterCar *m_masterCar = nullptr;
    Road *m_road = nullptr;
};