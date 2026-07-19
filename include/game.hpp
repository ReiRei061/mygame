#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
    // Propiedades de la ventana y lógica
    sf::RenderWindow m_window;
    bool m_isRunning;

    // Métodos privados del ciclo de juego (Game Loop)
    void processEvents();
    void update(float dt);
    void render();

public:
    Game();  // Constructor: Configura la ventana
    ~Game(); // Destructor: Limpia recursos si es necesario

    void run(); // Arranca el bucle principal
};