#include "states/MainMenuState.hpp"
#include "states/SelectSlotState.hpp"
#include "states/OptionsMenuState.hpp"
#include <iostream>

MainMenuState::MainMenuState(StateManager& stateManager, TextureManager& textureManager, 
                             FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window)
    : m_stateManager(stateManager), m_textureManager(textureManager), 
      m_fontManager(fontManager), m_audioManager(audioManager), m_window(window) {
    
    initUI();
}

void MainMenuState::initUI() {

    // Fondo del juego
    m_textureManager.loadTexture("main_menu_bg", "assets/menus/menu01.png");
    m_backgroundSprite.setTexture(m_textureManager.getTexture("main_menu_bg"));

    sf::Vector2u textureSize = m_backgroundSprite.getTexture()->getSize();
    m_backgroundSprite.setScale(
        800.0f / static_cast<float>(textureSize.x),
        600.0f / static_cast<float>(textureSize.y)
    );

    // Título del Juego
    if (m_fontManager.hasFont("main_font")) {
        m_titleText.setFont(m_fontManager.getFont("main_font"));
        m_titleText.setString("MY GAME");
        m_titleText.setCharacterSize(48);
        
        m_titleText.setFillColor(sf::Color(255, 235, 180));
        m_titleText.setOutlineColor(sf::Color(35, 25, 15, 220));
        m_titleText.setOutlineThickness(3.0f);

        sf::FloatRect bounds = m_titleText.getLocalBounds();
        m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        m_titleText.setPosition(400.0f, 120.0f);
    }

    const sf::Font& font = m_fontManager.getFont("main_font");

    // Botón: JUGAR
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 240.0f), sf::Vector2f(200.0f, 50.0f),
        font, "JUGAR", 22,
        [this]() {
            m_stateManager.pushState(std::make_unique<SelectSlotState>(m_stateManager, m_textureManager, m_fontManager));
        }
    ));

    // Botón: OPCIONES (Apila el nuevo OptionsMenuState)
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 310.0f), sf::Vector2f(200.0f, 50.0f),
        font, "OPCIONES", 22,
        [this]() {
            m_stateManager.pushState(std::make_unique<OptionsMenuState>(
                m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window
            ));
        }
    ));

    // Botón: SALIR
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 380.0f), sf::Vector2f(200.0f, 50.0f),
        font, "SALIR", 22,
        [this]() {
            m_stateManager.popState();
        }
    ));
}

void MainMenuState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    for (auto& button : m_buttons) {
        button->handleEvent(event, window);
    }
}

void MainMenuState::update(float dt) {
}

void MainMenuState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 30));

    window.draw(m_backgroundSprite);
    window.draw(m_titleText);

    for (auto& button : m_buttons) {
        button->render(window);
    }
}