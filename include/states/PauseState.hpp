#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AudioManager.hpp"
#include "ui/Button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class PauseState : public State {
public:
    PauseState(StateManager& stateManager, TextureManager& textureManager, 
               FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window);
    ~PauseState() override = default;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;
    AudioManager& m_audioManager;
    sf::RenderWindow& m_window;

    sf::RectangleShape m_overlay; // Fondo semitransparente
    sf::RectangleShape m_panel;   // Cuadro de diálogo principal
    sf::Text m_titleText;
    
    std::vector<std::unique_ptr<Button>> m_mainButtons;
    std::vector<std::unique_ptr<Button>> m_confirmButtons;

    bool m_showConfirmMenu{ false }; // Controla si se muestra la confirmación (Si/No)

    void initUI();
};

#endif // PAUSESTATE_HPP