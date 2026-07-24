#include "Game.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "[EXCEPTION] Error critico en el juego: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}