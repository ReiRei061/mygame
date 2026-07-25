#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"

class Game {
public:
    Game();
    ~Game() = default;

    // Deshabilitar copia
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Método principal para iniciar el bucle de juego
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void toggleFullscreen();
    void updateView(float windowWidth, float windowHeight);

    sf::RenderWindow m_window;
    sf::View m_gameView;
    bool m_isFullscreen{ true };

    sf::Clock m_clock;

    // Gestores de recursos
    TextureManager m_textureManager;
    FontManager m_fontManager;
    AudioManager m_audioManager;

    // Gestor de estados
    StateManager m_stateManager;
};

#endif // GAME_HPP