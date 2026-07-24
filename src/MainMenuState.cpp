#include "MainMenuState.hpp"
#include <iostream>

MainMenuState::MainMenuState(StateManager& stateManager, TextureManager& textureManager, FontManager& fontManager)
    : m_stateManager(stateManager), m_textureManager(textureManager), m_fontManager(fontManager) {
    
    initUI();
}

void MainMenuState::initUI() {
    // Título del Juego
    if (m_fontManager.hasFont("main_font")) {
        m_titleText.setFont(m_fontManager.getFont("main_font"));
        m_titleText.setString("MY GAME");
        m_titleText.setCharacterSize(48);
        m_titleText.setFillColor(sf::Color::White);

        sf::FloatRect bounds = m_titleText.getLocalBounds();
        m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        m_titleText.setPosition(400.0f, 120.0f);
    }

    const sf::Font& font = m_fontManager.getFont("main_font");

    // Botón: JUGAR
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 240.0f), sf::Vector2f(200.0f, 50.0f),
        font, "JUGAR", 22,
        []() {
            std::cout << "[INFO] Iniciar juego presionado!\n";
            // Aquí luego cambiaremos a PlayState
        }
    ));

    // Botón: OPCIONES
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 310.0f), sf::Vector2f(200.0f, 50.0f),
        font, "OPCIONES", 22,
        []() {
            std::cout << "[INFO] Opciones presionado!\n";
        }
    ));

    // Botón: SALIR
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 380.0f), sf::Vector2f(200.0f, 50.0f),
        font, "SALIR", 22,
        [this]() {
            // Elimina los estados para salir de la pila limpiamente
            m_stateManager.popState();
        }
    ));
}

void MainMenuState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    // Cada botón procesa el clic usando las coordenadas reales de la ventana
    for (auto& button : m_buttons) {
        button->handleEvent(event, window);
    }
}

void MainMenuState::update(float dt) {
    // Lógica adicional de animación del menú
}

void MainMenuState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 30));

    window.draw(m_titleText);

    for (auto& button : m_buttons) {
        button->render(window);
    }
}