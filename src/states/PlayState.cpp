#include "states/PlayState.hpp"
#include "states/PauseState.hpp"
#include "core/SaveSystem.hpp"
#include <iostream>
#include <cctype>

PlayState::PlayState(StateManager& stateManager, TextureManager& textureManager, 
                     FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window,
                     const std::string& slotName, const std::string& difficulty)
    : m_stateManager(stateManager), m_textureManager(textureManager), 
      m_fontManager(fontManager), m_audioManager(audioManager), m_window(window),
      m_slotName(slotName), m_difficulty(difficulty), m_mapManager(textureManager) {

    // 1. Extraer ID numérico del slot (ej: "Slot_1" -> 1)
    int slotIndex = 1;
    for (char c : m_slotName) {
        if (std::isdigit(c)) {
            slotIndex = c - '0';
            break;
        }
    }

    // 2. Cargar datos si existen, o inicializar nueva partida
    SaveData data;
    if (SaveSystem::exists(slotIndex) && SaveSystem::loadGame(slotIndex, data)) {
        m_mapManager.loadMap(data.currentMap);
        m_player.setPosition(sf::Vector2f(data.playerX, data.playerY));
    } else {
        m_mapManager.loadMap("map01");
        m_player.setPosition(sf::Vector2f(200.0f, 300.0f));
        
        data.slotId = slotIndex;
        data.difficulty = m_difficulty;
        data.currentMap = m_mapManager.getCurrentMap();
        data.playerX = m_player.getPosition().x;
        data.playerY = m_player.getPosition().y;

        SaveSystem::saveGame(slotIndex, data);
    }

    setupPortalsForCurrentMap();
}

void PlayState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        // Abrir pausa con ESC
        if (event.key.code == sf::Keyboard::Escape) {
            m_stateManager.pushState(std::make_unique<PauseState>(
                m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window
            ));
            return;
        }

        // Tecla de salto en plataformas
        if (event.key.code == sf::Keyboard::Space) {
            m_player.jump();
        }
    }
}

void PlayState::setupPortalsForCurrentMap() {
    m_portals.clear();

    // Configurar portales específicos cuando estamos en map02
    if (m_mapManager.getCurrentMap() == "map02") {
        // Portal 1: Círculo Mágico Verde
        m_portals.push_back(Portal(
            sf::Vector2f(510.0f, 150.0f), 
            sf::Vector2f(40.0f, 40.0f), 
            PlayerMode::Platformer2D
        ));

        // Portal 2: Entrada a la Cueva de Hongos (Esquina inferior derecha)
        m_portals.push_back(Portal(
            sf::Vector2f(720.0f, 500.0f), 
            sf::Vector2f(50.0f, 50.0f), 
            PlayerMode::Platformer2D
        ));
    }
}

void PlayState::checkScreenTransitions() {
    sf::Vector2f pos = m_player.getPosition();

    // --- TRANSICIÓN: map01 -> map02 (Salida por el borde derecho) ---
    if (m_mapManager.getCurrentMap() == "map01" && pos.x > 800.0f) {
        m_mapManager.loadMap("map02");
        setupPortalsForCurrentMap();
        m_player.setPosition(sf::Vector2f(20.0f, pos.y)); // Aparecer por la izquierda
    }
    // --- TRANSICIÓN: map02 -> map01 (Regreso por el borde izquierdo) ---
    else if (m_mapManager.getCurrentMap() == "map02" && pos.x < 0.0f) {
        m_mapManager.loadMap("map01");
        setupPortalsForCurrentMap();
        m_player.setPosition(sf::Vector2f(780.0f, pos.y)); // Aparecer por la derecha
    }
}

void PlayState::checkPortalCollisions() {
    for (const auto& portal : m_portals) {
        if (portal.checkCollision(m_player.getBounds())) {
            if (m_player.getMode() != portal.getTargetMode()) {
                m_player.setMode(portal.getTargetMode());
                std::cout << "[PlayState] Portal activado: Cambio a modo PLATAFORMAS 2D!\n";
            }
        }
    }
}

void PlayState::update(float dt) {
    // 1. Capturar entrada de movimiento
    m_player.handleInput();

    // 2. Actualizar posición y física del jugador
    m_player.update(dt);

    // 3. Evaluar cambios de mapa y colisiones con portales
    checkScreenTransitions();
    checkPortalCollisions();
}

void PlayState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // 1. Dibujar el mapa actual
    m_mapManager.render(window);

    // 2. Dibujar portales si existen en la pantalla
    for (auto& portal : m_portals) {
        portal.render(window);
    }

    // 3. Dibujar al personaje
    m_player.render(window);
}