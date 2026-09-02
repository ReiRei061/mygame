#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include "State.hpp"
#include <stack>
#include <memory>

class StateManager {
public:
    StateManager() = default;

    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);
    void clearStates(); // Solicita la limpieza diferida

    void processPendingChanges(); // Se ejecuta al final de update()

    void handleInput(const sf::Event& event, const sf::RenderWindow& window);
    void update(float dt);
    void render(sf::RenderWindow& window);

    bool isEmpty() const { return m_states.empty(); }

private:
    std::stack<std::unique_ptr<State>> m_states;
    
    // Variables para cambios diferidos
    bool m_clearRequested{ false };
    std::unique_ptr<State> m_pendingState{ nullptr };
    bool m_popRequested{ false };
};

#endif // STATEMANAGER_HPP