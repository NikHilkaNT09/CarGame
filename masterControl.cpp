#include "masterControl.h"

MasterControl::MasterControl(sf::Vector2f &window)
{
    m_masterCar = new MasterCar(window);
    m_road = new Road(window);
}