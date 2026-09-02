#include "states/OptionsMenuState.hpp"
#include <iostream>

OptionsMenuState::OptionsMenuState(StateManager& stateManager, TextureManager& textureManager,
                                   FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window)
    : m_stateManager(stateManager), m_textureManager(textureManager), 
      m_fontManager(fontManager), m_audioManager(audioManager), m_window(window) {

    ConfigSystem::loadConfig(m_config);

    if (m_textureManager.hasTexture("main_menu_bg")) {
        m_backgroundSprite.setTexture(m_textureManager.getTexture("main_menu_bg"));
    }

    buildMainUI();
}

void OptionsMenuState::applyVideoSettings() {
    // Recreación de la ventana para Pantalla Completa vs Ventana
    sf::Uint32 style = m_config.fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    m_window.create(sf::VideoMode(800, 600), "My Game", style);

    if (m_config.vsync) {
        m_window.setVerticalSyncEnabled(true);
    } else {
        m_window.setVerticalSyncEnabled(false);
        m_window.setFramerateLimit(m_config.targetFPS);
    }

    ConfigSystem::saveConfig(m_config);
}

void OptionsMenuState::buildMainUI() {
    m_uiButtons.clear();
    m_labels.clear();
    const sf::Font& font = m_fontManager.getFont("main_font");

    m_titleText.setFont(font);
    m_titleText.setString("OPCIONES DE JUEGO");
    m_titleText.setCharacterSize(36);
    m_titleText.setFillColor(sf::Color(255, 235, 180));
    sf::FloatRect bounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    m_titleText.setPosition(400.0f, 70.0f);

    // 1. Botón Pantalla Completa
    std::string fsLabel = m_config.fullscreen ? "PANTALLA COMPLETA: SI" : "PANTALLA COMPLETA: NO";
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(220.0f, 160.0f), sf::Vector2f(360.0f, 50.0f), font, fsLabel, 18,
        [this]() {
            m_config.fullscreen = !m_config.fullscreen;
            applyVideoSettings();
            m_needsUIUpdate = true;
        }
    ));

    // 2. Botón FPS / VSync
    std::string fpsLabel = m_config.vsync ? "FPS: VSYNC (60Hz)" : "FPS: " + std::to_string(m_config.targetFPS);
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(220.0f, 230.0f), sf::Vector2f(360.0f, 50.0f), font, fpsLabel, 18,
        [this]() {
            if (m_config.vsync) {
                m_config.vsync = false;
                m_config.targetFPS = 30;
            } else if (m_config.targetFPS == 30) {
                m_config.targetFPS = 60;
            } else if (m_config.targetFPS == 60) {
                m_config.targetFPS = 120;
            } else {
                m_config.vsync = true;
            }
            applyVideoSettings();
            m_needsUIUpdate = true;
        }
    ));

    // 3. Entrar a Submenú de Sonido
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(220.0f, 300.0f), sf::Vector2f(360.0f, 50.0f), font, "AJUSTES DE AUDIO >", 18,
        [this]() {
            m_currentSubMenu = OptionsSubMenu::AudioOptions;
            m_needsUIUpdate = true;
        }
    ));

    // 4. Botón Volver al Menú Principal
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(50.0f, 510.0f), sf::Vector2f(140.0f, 40.0f), font, "VOLVER", 18,
        [this]() { m_stateManager.popState(); }
    ));
}

void OptionsMenuState::buildAudioUI() {
    m_uiButtons.clear();
    m_labels.clear();
    const sf::Font& font = m_fontManager.getFont("main_font");

    m_titleText.setString("CONFIGURACION DE AUDIO");
    sf::FloatRect bounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    m_titleText.setPosition(400.0f, 70.0f);

    // Master Volume Controls
    std::string masterStr = "MASTER: " + std::to_string(static_cast<int>(m_config.masterVolume)) + "%";
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(180.0f, 170.0f), sf::Vector2f(50.0f, 40.0f), font, "-", 20,
        [this]() {
            m_config.masterVolume = std::max(0.0f, m_config.masterVolume - 10.0f);
            ConfigSystem::saveConfig(m_config);
            m_needsUIUpdate = true;
        }
    ));
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(570.0f, 170.0f), sf::Vector2f(50.0f, 40.0f), font, "+", 20,
        [this]() {
            m_config.masterVolume = std::min(100.0f, m_config.masterVolume + 10.0f);
            ConfigSystem::saveConfig(m_config);
            m_needsUIUpdate = true;
        }
    ));

    // Music Volume Controls
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(180.0f, 250.0f), sf::Vector2f(50.0f, 40.0f), font, "-", 20,
        [this]() {
            m_config.musicVolume = std::max(0.0f, m_config.musicVolume - 10.0f);
            ConfigSystem::saveConfig(m_config);
            m_needsUIUpdate = true;
        }
    ));
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(570.0f, 250.0f), sf::Vector2f(50.0f, 40.0f), font, "+", 20,
        [this]() {
            m_config.musicVolume = std::min(100.0f, m_config.musicVolume + 10.0f);
            ConfigSystem::saveConfig(m_config);
            m_needsUIUpdate = true;
        }
    ));

    // SFX Volume Controls
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(180.0f, 330.0f), sf::Vector2f(50.0f, 40.0f), font, "-", 20,
        [this]() {
            m_config.sfxVolume = std::max(0.0f, m_config.sfxVolume - 10.0f);
            ConfigSystem::saveConfig(m_config);
            m_needsUIUpdate = true;
        }
    ));
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(570.0f, 330.0f), sf::Vector2f(50.0f, 40.0f), font, "+", 20,
        [this]() {
            m_config.sfxVolume = std::min(100.0f, m_config.sfxVolume + 10.0f);
            ConfigSystem::saveConfig(m_config);
            m_needsUIUpdate = true;
        }
    ));

    // Volver a Opciones Principales
    m_uiButtons.push_back(std::make_unique<Button>(
        sf::Vector2f(50.0f, 510.0f), sf::Vector2f(140.0f, 40.0f), font, "ATRAS", 18,
        [this]() {
            m_currentSubMenu = OptionsSubMenu::MainOptions;
            m_needsUIUpdate = true;
        }
    ));
}

void OptionsMenuState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        if (m_currentSubMenu == OptionsSubMenu::AudioOptions) {
            m_currentSubMenu = OptionsSubMenu::MainOptions;
            m_needsUIUpdate = true;
        } else {
            m_stateManager.popState();
        }
        return;
    }

    for (auto& btn : m_uiButtons) {
        btn->handleEvent(event, window);
    }
}

void OptionsMenuState::update(float dt) {
    if (m_needsUIUpdate) {
        if (m_currentSubMenu == OptionsSubMenu::MainOptions) {
            buildMainUI();
        } else {
            buildAudioUI();
        }
        m_needsUIUpdate = false;
    }
}

void OptionsMenuState::render(sf::RenderWindow& window) {
    window.draw(m_backgroundSprite);
    window.draw(m_titleText);

    for (auto& btn : m_uiButtons) {
        btn->render(window);
    }
}