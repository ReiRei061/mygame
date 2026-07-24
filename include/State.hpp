#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class State {
public:
    virtual ~State() = default;

    // 💡 Le agregamos la referencia a RenderWindow
    virtual void handleInput(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

#endif // STATE_HPP