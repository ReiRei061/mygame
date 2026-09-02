#include "entities/Player.hpp"
#include <cmath>

Player::Player() {
    m_shape.setSize(sf::Vector2f(32.0f, 32.0f));
    m_shape.setFillColor(sf::Color::Cyan); // Cian en modo 3/4
    m_shape.setOutlineThickness(2.0f);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOrigin(16.0f, 16.0f);
    m_shape.setPosition(400.0f, 300.0f);
}

void Player::setMode(PlayerMode mode) {
    m_mode = mode;
    m_velocity = sf::Vector2f(0.0f, 0.0f);
    
    // Cambiamos el color para saber visualmente en qué modo estamos
    if (m_mode == PlayerMode::TopDown3_4) {
        m_shape.setFillColor(sf::Color::Cyan);
    } else {
        m_shape.setFillColor(sf::Color::Yellow); // Amarillo en Plataformas
    }
}

void Player::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
}

void Player::jump() {
    if (m_mode == PlayerMode::Platformer2D && m_isGrounded) {
        m_velocity.y = m_jumpForce;
        m_isGrounded = false;
    }
}

void Player::handleInput() {
    sf::Vector2f dir(0.0f, 0.0f);

    if (m_mode == PlayerMode::TopDown3_4) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1.0f;

        if (dir.x != 0.0f || dir.y != 0.0f) {
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            dir /= len;
        }
        m_velocity = dir * m_speed;

    } else if (m_mode == PlayerMode::Platformer2D) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1.0f;

        m_velocity.x = dir.x * m_speed;
    }
}

void Player::update(float dt) {
    if (m_mode == PlayerMode::TopDown3_4) {
        m_shape.move(m_velocity * dt);

    } else if (m_mode == PlayerMode::Platformer2D) {
        m_velocity.y += m_gravity * dt;
        m_shape.move(m_velocity * dt);

        // Suelo temporal a Y=500 px
        if (m_shape.getPosition().y >= 500.0f) {
            m_shape.setPosition(m_shape.getPosition().x, 500.0f);
            m_velocity.y = 0.0f;
            m_isGrounded = true;
        }
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(m_shape);
}