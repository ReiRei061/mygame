#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/System/Vector2.hpp>

// Evento emitido cuando el jugador recibe daño
struct PlayerDamagedEvent {
    int currentHealth;
    int damageTaken;
};

// Evento emitido cuando el jugador cambia de zona o puntuación
struct ScoreUpdatedEvent {
    int newScore;
};

// Evento para solicitar un guardado de partida desde la UI
struct SaveGameRequestedEvent {
    int slotIndex;
};

#endif // EVENTS_HPP