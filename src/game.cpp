#include "Game.hpp"
#include "SplashState.hpp"

Game::Game()
    : m_window(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::Fullscreen) {
    
    m_window.setFramerateLimit(60);

    // 1. Definir la resolución interna lógica del juego (800x600)
    m_gameView.setSize(800.0f, 600.0f);
    m_gameView.setCenter(400.0f, 300.0f);

    // 2. Ajustar el Viewport a la resolución real del monitor para calcular barras negras
    updateView(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y));

    // 3. Cargar el primer estado
    m_stateManager.changeState(std::make_unique<SplashState>(m_stateManager, m_textureManager, m_fontManager));
}

void Game::run() {
    // Aplicar transiciones pendientes iniciales
    m_stateManager.update(0.0f);
    
    while (m_window.isOpen() && !m_stateManager.isEmpty()) {
        float dt = m_clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        // 1. Manejo de redimensión (Maximizar / Arrastrar bordes)
        if (event.type == sf::Event::Resized) {
            updateView(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        }

        // 2. Detectar Alt + Enter para Pantalla Completa
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter && event.key.alt) {
                toggleFullscreen();
            }
        }

        m_stateManager.handleInput(event, m_window);
    }
}

void Game::updateView(float windowWidth, float windowHeight) {
    float targetRatio = 800.0f / 600.0f;
    float windowRatio = windowWidth / windowHeight;

    float viewportX = 0.0f;
    float viewportY = 0.0f;
    float viewportWidth = 1.0f;
    float viewportHeight = 1.0f;

    if (windowRatio > targetRatio) {
        // Barras negras a los lados (Pillarbox)
        viewportWidth = targetRatio / windowRatio;
        viewportX = (1.0f - viewportWidth) / 2.0f;
    } else {
        // Barras negras arriba/abajo (Letterbox)
        viewportHeight = windowRatio / targetRatio;
        viewportY = (1.0f - viewportHeight) / 2.0f;
    }

    m_gameView.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));
    m_window.setView(m_gameView);
}

void Game::toggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;

    if (m_isFullscreen) {
        m_window.create(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::Fullscreen);
    } else {
        m_window.create(sf::VideoMode(800, 600), "My Game", sf::Style::Default);
    }

    m_window.setFramerateLimit(60);

    // Reajustar la vista al nuevo tamaño de ventana
    updateView(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y));
}

// AQUÍ ESTABA LA FUNCIÓN QUE FALTABA
void Game::update(float dt) {
    m_stateManager.update(dt);
}

void Game::render() {
    m_window.clear(sf::Color::Black);

    m_stateManager.render(m_window);

    m_window.display();
}