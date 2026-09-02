#include "states/StateManager.hpp"

void StateManager::clearStates() {
    m_clearRequested = true;
}

void StateManager::changeState(std::unique_ptr<State> state) {
    m_clearRequested = true;
    m_pendingState = std::move(state);
}

void StateManager::popState() {
    m_popRequested = true;
}

void StateManager::pushState(std::unique_ptr<State> state) {
    m_pendingState = std::move(state);
}

void StateManager::processPendingChanges() {
    // 1. Limpiar toda la pila si se solicitó
    if (m_clearRequested) {
        while (!m_states.empty()) {
            m_states.pop();
        }
        m_clearRequested = false;
    }

    // 2. Eliminar el estado superior si se pidió pop
    if (m_popRequested && !m_states.empty()) {
        m_states.pop();
        m_popRequested = false;
    }

    // 3. Agregar el nuevo estado si hay alguno pendiente
    if (m_pendingState) {
        m_states.push(std::move(m_pendingState));
    }
}

void StateManager::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (!m_states.empty()) {
        m_states.top()->handleInput(event, window);
    }
}

void StateManager::update(float dt) {
    if (!m_states.empty()) {
        m_states.top()->update(dt);
    }
}

void StateManager::render(sf::RenderWindow& window) {
    // Para que el PlayState se siga viendo detrás de la pausa:
    // Si hay más de un estado, dibujamos desde el fondo si es necesario,
    // o simplemente el estado actual.
    if (!m_states.empty()) {
        m_states.top()->render(window);
    }
}