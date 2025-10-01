#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string.h>

class Button{

public:
    explicit Button(std::string text);

    std::pair<bool, std::string> checkClick(sf::Vector2f &mouseClick);
    void setButtonPositions(sf::RenderWindow &window);

    sf::RectangleShape getStartButton() const;
    sf::RectangleShape getStopButton() const;
private:
    sf::RectangleShape* m_startButton = nullptr;
    sf::RectangleShape* m_stopButton = nullptr;
};