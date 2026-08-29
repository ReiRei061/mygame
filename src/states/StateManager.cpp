#include "states/StateManager.hpp"

// Registra la intención de reemplazar el estado actual por uno nuevo
void StateManager::changeState(std::unique_ptr<State> newState) {
    m_pendingState = std::move(newState); // Guarda el nuevo estado
    m_pendingAction = PendingAction::Change; // Marca la acción como "Cambiar"
}

// Registra la intención de apilar un nuevo estado sobre el actual
void StateManager::pushState(std::unique_ptr<State> newState) {
    m_pendingState = std::move(newState); // Guarda el nuevo estado a superponer
    m_pendingAction = PendingAction::Push; // Marca la acción como "Apilar"
}

// Registra la intención de desapilar el estado actual
void StateManager::popState() {
    m_pendingAction = PendingAction::Pop; // Marca la acción como "Desapilar"
}

// Envía el evento de SFML (teclado/mouse) al estado que está en la cima de la pila
void StateManager::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (!m_states.empty()) {
        m_states.top()->handleInput(event, window);
    }
}
// Ejecuta las modificaciones diferidas de la pila y actualiza el estado activo
void StateManager::update(float dt) {
    applyPendingChanges(); // Primero procesa cambios de estado pendientes para evitar errores de memoria

    if (!m_states.empty()) {
        m_states.top()->update(dt); // Actualiza la lógica del estado actual
    }
}

// Dibuja en pantalla el estado activo
void StateManager::render(sf::RenderWindow& window) {
    if (!m_states.empty()) {
        m_states.top()->render(window); // Dibuja los gráficos del estado que esté en la cima
    }
}

// Consulta si la pila está vacía
bool StateManager::isEmpty() const {
    return m_states.empty();
}

// Procesa de forma segura las modificaciones a la pila (evita eliminar un estado mientras ejecuta su propio update)
void StateManager::applyPendingChanges() {
    if (m_pendingAction == PendingAction::None) return; // Si no hay cambios pendientes, no hace nada

    switch (m_pendingAction) {
        case PendingAction::Change:
            // Vacía por completo la pila destruyendo los estados anteriores
            while (!m_states.empty()) {
                m_states.pop();
            }
            // Coloca el nuevo estado como el único en la pila
            if (m_pendingState) {
                m_states.push(std::move(m_pendingState));
            }
            break;

        case PendingAction::Push:
            // Apila el nuevo estado encima de los existentes (el anterior queda pausado abajo)
            if (m_pendingState) {
                m_states.push(std::move(m_pendingState));
            }
            break;

        case PendingAction::Pop:
            // Elimina el estado superior volviendo al que estaba inmediatamente abajo
            if (!m_states.empty()) {
                m_states.pop();
            }
            break;

        case PendingAction::None:
            break;
    }

    // Restablece las variables de control diferido para el siguiente frame
    m_pendingAction = PendingAction::None;
    m_pendingState.reset();
}