#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include "states/State.hpp"
#include "states/StateManager.hpp"
#include "core/FontManager.hpp"
#include "core/SaveSystem.hpp"
#include <SFML/Graphics/Text.hpp>

class PlayState : public State {
public:
    PlayState(StateManager& stateManager, FontManager& fontManager, const SaveData& saveData);

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    FontManager& m_fontManager;
    SaveData m_saveData;

    sf::Text m_infoText;
    sf::Text m_instructionText;
};

#endif