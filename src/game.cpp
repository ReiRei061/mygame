#include "Game.hpp"
#include "SplashState.hpp"

Game::Game()
    : m_window(sf::VideoMode(800, 600), "My Game", sf::Style::Close | sf::Style::Titlebar) {
    
    // Limitar FPS para un rendimiento suave
    m_window.setFramerateLimit(60);

    // Arrancamos el juego metiendo el SplashState como estado inicial
    m_stateManager.changeState(std::make_unique<SplashState>(m_stateManager, m_textureManager, m_fontManager));
}

void Game::run() {
    // Aplicar transiciones pendientes iniciales (por si changeState es diferido)
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

        // Delegar evento a la maquina de estados pasando la ventana
        m_stateManager.handleInput(event, m_window);
    }
}

void Game::update(float dt) {
    m_stateManager.update(dt);
}

void Game::render() {
    m_window.clear(sf::Color::Black);

    m_stateManager.render(m_window);

    m_window.display();
}