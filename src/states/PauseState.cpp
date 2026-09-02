#include "states/PauseState.hpp"
#include "states/OptionsMenuState.hpp"
#include "states/MainMenuState.hpp"
#include <iostream>

PauseState::PauseState(StateManager& stateManager, TextureManager& textureManager, 
                       FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window)
    : m_stateManager(stateManager), m_textureManager(textureManager), 
      m_fontManager(fontManager), m_audioManager(audioManager), m_window(window) {

    // Capa de oscurecimiento sobre el juego
    m_overlay.setSize(sf::Vector2f(800.0f, 600.0f));
    m_overlay.setFillColor(sf::Color(0, 0, 0, 150));

    // Panel flotante central
    m_panel.setSize(sf::Vector2f(360.0f, 320.0f));
    m_panel.setFillColor(sf::Color(25, 25, 35, 230));
    m_panel.setOutlineThickness(2.0f);
    m_panel.setOutlineColor(sf::Color::Cyan);
    m_panel.setOrigin(180.0f, 160.0f);
    m_panel.setPosition(400.0f, 300.0f);

    initUI();
}

void PauseState::initUI() {
    const sf::Font& font = m_fontManager.getFont("main_font");

    if (m_fontManager.hasFont("main_font")) {
        m_titleText.setFont(font);
        m_titleText.setString("PAUSA");
        m_titleText.setCharacterSize(28);
        m_titleText.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = m_titleText.getLocalBounds();
        m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        m_titleText.setPosition(400.0f, 170.0f);
    }

    // --- BOTONES PRINCIPALES ---
    // Continuar
    m_mainButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(280.0f, 220.0f), sf::Vector2f(240.0f, 40.0f),
        font, "CONTINUAR", 18,
        [this]() { m_stateManager.popState(); } // Reanuda el juego
    ));

    // Opciones
    m_mainButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(280.0f, 275.0f), sf::Vector2f(240.0f, 40.0f),
        font, "OPCIONES", 18,
        [this]() {
            m_stateManager.pushState(std::make_unique<OptionsMenuState>(
                m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window
            ));
        }
    ));

    // Menú Principal (Abre confirmación Si/No)
    m_mainButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(280.0f, 330.0f), sf::Vector2f(240.0f, 40.0f),
        font, "MENU PRINCIPAL", 16,
        [this]() {
            m_showConfirmMenu = true;
            m_titleText.setString("¿SALIR AL MENU?");
            sf::FloatRect bounds = m_titleText.getLocalBounds();
            m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
            m_titleText.setPosition(400.0f, 200.0f);
        }
    ));

    // --- BOTONES DE CONFIRMACIÓN (SI / NO) ---
    // SI: Limpia todos los estados en la pila y vuelve a MainMenuState
    m_confirmButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(270.0f, 280.0f), sf::Vector2f(110.0f, 45.0f),
        font, "SI", 18,
        [this]() {
            m_stateManager.clearStates();
            m_stateManager.changeState(std::make_unique<MainMenuState>(
                m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window
            ));
        }
    ));

    // NO: Cancela la confirmación y regresa al menú de pausa
    m_confirmButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(420.0f, 280.0f), sf::Vector2f(110.0f, 45.0f),
        font, "NO", 18,
        [this]() {
            m_showConfirmMenu = false;
            m_titleText.setString("PAUSA");
            sf::FloatRect bounds = m_titleText.getLocalBounds();
            m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
            m_titleText.setPosition(400.0f, 170.0f);
        }
    ));
}

void PauseState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        if (m_showConfirmMenu) {
            // Si estaba en la pregunta Si/No, cancelar la confirmación
            m_showConfirmMenu = false;
            m_titleText.setString("PAUSA");
            sf::FloatRect bounds = m_titleText.getLocalBounds();
            m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
            m_titleText.setPosition(400.0f, 170.0f);
        } else {
            // Despausar con ESC
            m_stateManager.popState();
        }
        return;
    }

    if (!m_showConfirmMenu) {
        for (auto& btn : m_mainButtons) btn->handleEvent(event, window);
    } else {
        for (auto& btn : m_confirmButtons) btn->handleEvent(event, window);
    }
}

void PauseState::update(float dt) {}

void PauseState::render(sf::RenderWindow& window) {
    // Dibujar el overlay y el cuadro del panel flotante
    window.draw(m_overlay);
    window.draw(m_panel);
    window.draw(m_titleText);

    if (!m_showConfirmMenu) {
        for (auto& btn : m_mainButtons) btn->render(window);
    } else {
        for (auto& btn : m_confirmButtons) btn->render(window);
    }
}