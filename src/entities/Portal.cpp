#include "entities/Portal.hpp"

Portal::Portal(sf::Vector2f position, sf::Vector2f size, PlayerMode targetMode, std::string targetMap)
    : m_targetMode(targetMode), m_targetMap(targetMap) {
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(150, 50, 250, 120)); // Morado transparente
    m_shape.setOutlineThickness(2.0f);
    m_shape.setOutlineColor(sf::Color::Magenta);
}

bool Portal::checkCollision(const sf::FloatRect& playerBounds) const {
    return m_shape.getGlobalBounds().intersects(playerBounds);
}

void Portal::render(sf::RenderWindow& window) {
    window.draw(m_shape);
}