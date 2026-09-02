#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class Portal {
public:
    Portal(sf::Vector2f position, sf::Vector2f size, PlayerMode targetMode, std::string targetMap = "");

    bool checkCollision(const sf::FloatRect& playerBounds) const;
    void render(sf::RenderWindow& window);

    PlayerMode getTargetMode() const { return m_targetMode; }
    const std::string& getTargetMap() const { return m_targetMap; }

private:
    sf::RectangleShape m_shape;
    PlayerMode m_targetMode;
    std::string m_targetMap;
};

#endif // PORTAL_HPP