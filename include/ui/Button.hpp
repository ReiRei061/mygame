#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button {
public:
    // Callback que se ejecuta cuando el usuario hace clic en el botón
    using Action = std::function<void()>;

    Button(const sf::Vector2f& position, const sf::Vector2f& size, 
           const sf::Font& font, const std::string& text, 
           unsigned int characterSize, Action onClick);

    ~Button() = default;

    // Manejo de eventos de entrada (movimiento de ratón y clics)
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    // Dibuja el botón en la ventana
    void render(sf::RenderWindow& window);

    // Personalización de colores para los distintos estados
    void setColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& active);
    void setTextColor(const sf::Color& color);

private:
    enum class State { Normal, Hover, Active };

    sf::RectangleShape m_shape;
    sf::Text m_text;
    State m_state{ State::Normal };
    Action m_onClick;

    // Colores por defecto
    sf::Color m_normalColor{ 70, 70, 70 };
    sf::Color m_hoverColor{ 100, 100, 100 };
    sf::Color m_activeColor{ 150, 150, 150 };

    void updateColors();
    void centerText();
};

#endif // BUTTON_HPP