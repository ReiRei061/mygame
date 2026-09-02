#ifndef SELECTDIFFICULTYSTATE_HPP
#define SELECTDIFFICULTYSTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"
#include "ui/Button.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include <string>

class SelectDifficultyState : public State {
public:
    SelectDifficultyState(StateManager& stateManager, TextureManager& textureManager, 
                          FontManager& fontManager, AudioManager& audioManager, 
                          sf::RenderWindow& window, const std::string& slotName);
    ~SelectDifficultyState() override = default;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;
    AudioManager& m_audioManager;
    sf::RenderWindow& m_window;

    std::string m_selectedSlot;
    sf::Text m_titleText;
    std::vector<std::unique_ptr<Button>> m_buttons;

    void initUI();
    void startWithDifficulty(const std::string& difficulty);
};

#endif // SELECTDIFFICULTYSTATE_HPP