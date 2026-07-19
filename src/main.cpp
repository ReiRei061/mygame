#include 

int main() {
    // Crear la ventana del juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mi Juego SFML");

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 1. Limpiar la pantalla
        window.clear(sf::Color::Black);

        // 2. Dibujar los elementos del juego aquí
        // window.draw(...);

        // 3. Mostrar lo que se ha dibujado en la pantalla
        window.display();
    }

    return 0;
}