#ifndef SELECTSLOTSTATE_HPP
#define SELECTSLOTSTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "core/TextureManager.hpp"
#include "core/FontManager.hpp"
#include "core/AudioManager.hpp"
#include "ui/Button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class SelectSlotState : public State {
public:
    SelectSlotState(StateManager& stateManager, TextureManager& textureManager, 
                    FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window);

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void initUI();

    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;
    AudioManager& m_audioManager;
    sf::RenderWindow& m_window;
    sf::Sprite m_backgroundSprite;

    const sf::Font& m_font;
    bool m_needsRefresh{ false };

    std::vector<std::unique_ptr<Button>> m_buttons;
    std::vector<std::unique_ptr<Button>> m_deleteButtons;

    // Control del modal de confirmación de borrado
    int m_slotToDelete{ -1 }; // -1 indica que no hay ningún modal activo
    sf::Text m_confirmText;
    std::vector<std::unique_ptr<Button>> m_confirmButtons;
    sf::RectangleShape m_overlay;
};

#endif // SELECTSLOTSTATE_HPP