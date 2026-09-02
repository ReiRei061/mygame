#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"
#include "core/MapManager.hpp"
#include "entities/Player.hpp"
#include "entities/Portal.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PlayState : public State {
public:
    PlayState(StateManager& stateManager, TextureManager& textureManager, 
              FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window,
              const std::string& slotName, const std::string& difficulty);
    ~PlayState() override = default;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;
    AudioManager& m_audioManager;
    sf::RenderWindow& m_window;

    std::string m_difficulty;
    std::string m_slotName;

    MapManager m_mapManager;
    Player m_player;
    std::vector<Portal> m_portals;

    void checkScreenTransitions();
    void checkPortalCollisions();
    void setupPortalsForCurrentMap();
};

#endif // PLAYSTATE_HPP