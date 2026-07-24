#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "State.hpp"

class StateManager {
public:
    StateManager() = default;
    ~StateManager() = default;

    // Deshabilitar copias
    StateManager(const StateManager&) = delete;
    StateManager& operator=(const StateManager&) = delete;

    // Control de estados
    void changeState(std::unique_ptr<State> newState);
    void pushState(std::unique_ptr<State> newState);
    void popState();

    // Métodos de ciclo de vida
    void handleInput(const sf::Event& event, const sf::RenderWindow& window);
    void update(float dt);
    void render(sf::RenderWindow& window);

    bool isEmpty() const;

private:
    std::stack<std::unique_ptr<State>> m_states;
    
    // Gestión diferida de estados
    std::unique_ptr<State> m_pendingState;
    enum class PendingAction { None, Push, Pop, Change };
    PendingAction m_pendingAction{ PendingAction::None };

    void applyPendingChanges();
};

#endif // STATEMANAGER_HPP