#include "states/SplashState.hpp"
#include "states/MainMenuState.hpp" // Lo incluimos para poder hacer la transición
#include <algorithm>

SplashState::SplashState(StateManager& stateManager, TextureManager& textureManager, FontManager& fontManager)
    : m_stateManager(stateManager), m_textureManager(textureManager), m_fontManager(fontManager) {

    // Ruta hacia tu logo (ajusta la extensión .png si es .jpg)
    m_textureManager.loadTexture("logo", "assets/logos/logo01.png");
    
    // Carga de la fuente para el mensaje de saltar
    m_fontManager.loadFont("main_font", "assets/fonts/OpticLatin.ttf");

    // Configurar Sprite del Logo
    if (m_textureManager.hasTexture("logo")) {
        m_logoSprite.setTexture(m_textureManager.getTexture("logo"));
        
        // Centrar el origen de la imagen
        sf::FloatRect bounds = m_logoSprite.getLocalBounds();
        m_logoSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        m_logoSprite.setPosition(400.0f, 280.0f); // Centrado en pantalla de 800x600
    }

    // Configurar Texto de ayuda
    if (m_fontManager.hasFont("main_font")) {
        m_skipText.setFont(m_fontManager.getFont("main_font"));
        m_skipText.setString("Presiona ENTER o ESC para saltar");
        m_skipText.setCharacterSize(14);
        m_skipText.setFillColor(sf::Color(200, 200, 200, 150));
        
        sf::FloatRect textBounds = m_skipText.getLocalBounds();
        m_skipText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
        m_skipText.setPosition(400.0f, 540.0f);
    }
}

void SplashState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
            goToMainMenu();
        }
    }
}

void SplashState::update(float dt) {
    m_timer += dt;

    // Calcular la transparencia (Fade In durante el primer segundo, Fade Out en el último)
    if (m_timer < 1.0f) {
        m_alpha = m_timer * 255.0f; // Aparece progresivamente
    } else if (m_timer > m_duration - 1.0f) {
        m_alpha = (m_duration - m_timer) * 255.0f; // Desaparece progresivamente
    } else {
        m_alpha = 255.0f;
    }

    m_alpha = std::clamp(m_alpha, 0.0f, 255.0f);
    m_logoSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(m_alpha)));

    // Si termina el tiempo límite, cambiar automáticamente de estado
    if (m_timer >= m_duration) {
        goToMainMenu();
    }
}

void SplashState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(10, 10, 15)); // Fondo oscuro elegatne
    window.draw(m_logoSprite);
    window.draw(m_skipText);
}

void SplashState::goToMainMenu() {
    m_stateManager.changeState(std::make_unique<MainMenuState>(m_stateManager, m_textureManager, m_fontManager));
}