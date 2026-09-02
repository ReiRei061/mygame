#include "states/SelectDifficultyState.hpp"
#include "states/PlayState.hpp"
#include <iostream>

SelectDifficultyState::SelectDifficultyState(StateManager& stateManager, TextureManager& textureManager, 
                                             FontManager& fontManager, AudioManager& audioManager, 
                                             sf::RenderWindow& window, const std::string& slotName)
    : m_stateManager(stateManager), m_textureManager(textureManager), 
      m_fontManager(fontManager), m_audioManager(audioManager), 
      m_window(window), m_selectedSlot(slotName) {
    
    initUI();
}

void SelectDifficultyState::startWithDifficulty(const std::string& difficulty) {
    m_stateManager.changeState(std::make_unique<PlayState>(
        m_stateManager, 
        m_textureManager, 
        m_fontManager, 
        m_audioManager, 
        m_window,
        m_selectedSlot, // <-- ENVIAMOS EL SLOT ("Slot_1", etc.) 
        difficulty
    ));
}

void SelectDifficultyState::initUI() {
    const sf::Font& font = m_fontManager.getFont("main_font");

    if (m_fontManager.hasFont("main_font")) {
        m_titleText.setFont(font);
        m_titleText.setString("SELECCIONAR DIFICULTAD");
        m_titleText.setCharacterSize(32);
        m_titleText.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = m_titleText.getLocalBounds();
        m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        m_titleText.setPosition(400.0f, 100.0f);
    }

    // Botón FÁCIL
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(250.0f, 200.0f), sf::Vector2f(300.0f, 50.0f),
        font, "FACIL", 20,
        [this]() { startWithDifficulty("Facil"); }
    ));

    // Botón NORMAL
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(250.0f, 270.0f), sf::Vector2f(300.0f, 50.0f),
        font, "NORMAL", 20,
        [this]() { startWithDifficulty("Normal"); }
    ));

    // Botón DIFICIL
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(250.0f, 340.0f), sf::Vector2f(300.0f, 50.0f),
        font, "DIFICIL", 20,
        [this]() { startWithDifficulty("Dificil"); }
    ));

    // Botón VOLVER
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 440.0f), sf::Vector2f(200.0f, 45.0f),
        font, "VOLVER", 18,
        [this]() { m_stateManager.popState(); }
    ));
}

void SelectDifficultyState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    for (auto& button : m_buttons) {
        button->handleEvent(event, window);
    }
}

void SelectDifficultyState::update(float dt) {}

void SelectDifficultyState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(15, 15, 25));
    window.draw(m_titleText);

    for (auto& button : m_buttons) {
        button->render(window);
    }
}