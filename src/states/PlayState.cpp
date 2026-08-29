#include "states/PlayState.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

PlayState::PlayState(StateManager& stateManager, FontManager& fontManager, const SaveData& saveData)
    : m_stateManager(stateManager), m_fontManager(fontManager), m_saveData(saveData) {

    const sf::Font& font = m_fontManager.getFont("main_font");

    // Texto con la información de la partida cargada
    m_infoText.setFont(font);
    m_infoText.setString("PARTIDA EN JUEGO\nSlot: " + std::to_string(m_saveData.slotId) +
                         "\nDificultad: " + m_saveData.difficulty);
    m_infoText.setCharacterSize(28);
    m_infoText.setFillColor(sf::Color::White);
    
    sf::FloatRect bounds = m_infoText.getLocalBounds();
    m_infoText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    m_infoText.setPosition(400.0f, 250.0f);

    // Indicación para salir
    m_instructionText.setFont(font);
    m_instructionText.setString("Presiona ESC para salir al menu de slots");
    m_instructionText.setCharacterSize(18);
    m_instructionText.setFillColor(sf::Color(200, 200, 200));
    
    sf::FloatRect instBounds = m_instructionText.getLocalBounds();
    m_instructionText.setOrigin(instBounds.width / 2.0f, instBounds.height / 2.0f);
    m_instructionText.setPosition(400.0f, 450.0f);
}

void PlayState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_stateManager.popState(); // Salir del juego al menú
    }
}

void PlayState::update(float dt) {}

void PlayState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(15, 35, 20)); // Fondo verde oscuro representando el mundo
    window.draw(m_infoText);
    window.draw(m_instructionText);
}