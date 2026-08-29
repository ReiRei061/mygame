#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "Button.hpp"
#include <vector>
#include <memory>

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, TextureManager& textureManager, FontManager& fontManager);
    ~MainMenuState() override = default;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;

    sf::Text m_titleText;
    std::vector<std::unique_ptr<Button>> m_buttons;

    void initUI();
};

#endif // MAINMENUSTATE_HPP