#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

enum class PlayerMode {
    TopDown3_4,
    Platformer2D
};

class Player {
public:
    Player();

    void handleInput();
    void update(float dt);
    void render(sf::RenderWindow& window);

    void setMode(PlayerMode mode);
    PlayerMode getMode() const { return m_mode; }

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

    void jump();

private:
    sf::RectangleShape m_shape;
    PlayerMode m_mode{ PlayerMode::TopDown3_4 };

    sf::Vector2f m_velocity{ 0.0f, 0.0f };
    float m_speed{ 250.0f };
    float m_gravity{ 980.0f };
    float m_jumpForce{ -400.0f };
    bool m_isGrounded{ false };
};

#endif // PLAYER_HPP