#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, 
               const sf::Font& font, const std::string& text, 
               unsigned int characterSize, Action onClick)
    : m_onClick(onClick) {
    
    // Configuración del fondo
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(m_normalColor);

    // Configuración del texto
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(sf::Color::White);

    centerText();
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    // Convertir la posición del ratón de coordenadas de ventana a coordenadas de mundo
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    bool isHovered = m_shape.getGlobalBounds().contains(mouseWorldPos);

    if (isHovered) {
        if (m_state != State::Active) {
            m_state = State::Hover;
        }

        // Detectar si presionó el clic izquierdo
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            m_state = State::Active;
        }

        // Detectar cuando suelta el clic izquierdo (Acción del botón)
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (m_state == State::Active) {
                m_state = State::Hover;
                if (m_onClick) {
                    m_onClick(); // Ejecutar el callback asignado
                }
            }
        }
    } else {
        m_state = State::Normal;
    }

    updateColors();
}

void Button::render(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(m_text);
}

void Button::setColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& active) {
    m_normalColor = normal;
    m_hoverColor = hover;
    m_activeColor = active;
    updateColors();
}

void Button::setTextColor(const sf::Color& color) {
    m_text.setFillColor(color);
}

void Button::updateColors() {
    switch (m_state) {
        case State::Normal:
            m_shape.setFillColor(m_normalColor);
            break;
        case State::Hover:
            m_shape.setFillColor(m_hoverColor);
            break;
        case State::Active:
            m_shape.setFillColor(m_activeColor);
            break;
    }
}

void Button::centerText() {
    // Centrado perfecto del texto dentro del rectángulo del botón
    sf::FloatRect textBounds = m_text.getLocalBounds();
    sf::Vector2f buttonSize = m_shape.getSize();
    sf::Vector2f buttonPos = m_shape.getPosition();

    m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                     textBounds.top + textBounds.height / 2.0f);

    m_text.setPosition(buttonPos.x + buttonSize.x / 2.0f,
                       buttonPos.y + buttonSize.y / 2.0f);
}