#ifndef OPTIONS_MENU_STATE_HPP
#define OPTIONS_MENU_STATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"
#include "AudioManager.hpp"
#include "ui/Button.hpp"
#include "core/ConfigSystem.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <memory>

enum class OptionsSubMenu {
    MainOptions,
    AudioOptions
};

class OptionsMenuState : public State {
public:
    OptionsMenuState(StateManager& stateManager, TextureManager& textureManager, 
                     FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window);

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void buildMainUI();
    void buildAudioUI();
    void applyVideoSettings();

    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;
    AudioManager& m_audioManager;
    sf::RenderWindow& m_window;

    GameConfig m_config;
    OptionsSubMenu m_currentSubMenu{ OptionsSubMenu::MainOptions };

    sf::Sprite m_backgroundSprite;
    sf::Text m_titleText;

    std::vector<std::unique_ptr<Button>> m_uiButtons;
    std::vector<sf::Text> m_labels;

    bool m_needsUIUpdate{ false };
};

#endif