#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"
#include "ui/Button.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, TextureManager& textureManager, 
                  FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window);
    ~MainMenuState() override = default;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;
    AudioManager& m_audioManager;
    sf::RenderWindow& m_window;

    sf::Text m_titleText;
    sf::Sprite m_backgroundSprite;
    std::vector<std::unique_ptr<Button>> m_buttons;
    
    void initUI();
};

#endif // MAINMENUSTATE_HPP