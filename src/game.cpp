#include "Game.hpp"

Game::Game() : m_isRunning(true) {
    // Inicializar la ventana con resolución 800x600 y 60 FPS límite
    m_window.create(sf::VideoMode(800, 600), "Mi Juego SFML");
    m_window.setFramerateLimit(60);
}

Game::~Game() {
    // El destructor de sf::RenderWindow se encarga de cerrarla automáticamente
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        // Cerrar el juego si se presiona la 'X' de la ventana
        if (event.type == sf::Event::Closed) {
            m_isRunning = false;
            m_window.close();
        }
        
        // Aquí puedes capturar eventos de teclado o mouse específicos
    }
}

void Game::update(float dt) {
    // Aquí irá toda la lógica física, movimiento de personajes, colisiones, etc.
    // 'dt' (Delta Time) servirá más adelante para que el movimiento sea fluido
}

void Game::render() {
    // 1. Limpiar la pantalla con un color de fondo (Gris oscuro en este caso)
    m_window.clear(sf::Color(30, 30, 30));

    // 2. Aquí va la lógica de dibujo. Ejemplo: m_window.draw(miPersonaje);

    // 3. Mostrar lo que se dibujó en la ventana
    m_window.display();
}

void Game::run() {
    sf::Clock clock;

    // El Bucle Principal
    while (m_isRunning && m_window.isOpen()) {
        // Calcular el Delta Time (tiempo que tardó el frame anterior)
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}