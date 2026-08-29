#ifndef SELECT_SLOT_STATE_HPP
#define SELECT_SLOT_STATE_HPP

#include "states/State.hpp"
#include "core/SaveSystem.hpp"
#include "states/StateManager.hpp"
#include "core/TextureManager.hpp"
#include "core/FontManager.hpp"
#include "ui/Button.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <memory>
#include <string>

enum class DialogType { None, DifficultySelection, ConfirmContinue, ConfirmDelete };

class SelectSlotState : public State {
public:
    SelectSlotState(StateManager& stateManager, TextureManager& textureManager, FontManager& fontManager);

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void initUI();
    void openDialog(DialogType type, int slotIndex);
    void closeDialog();
    void updateSlotUI(); // Recarga la UI al borrar una partida

    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;

    sf::Sprite m_backgroundSprite;
    sf::Text m_titleText;

    bool m_slotHasSave[3]{ false, true, false };
    std::vector<std::unique_ptr<Button>> m_slotButtons;
    std::vector<std::unique_ptr<Button>> m_deleteButtons; // Botones para borrar
    std::unique_ptr<Button> m_backButton;

    // Pop-up / Diálogo
    DialogType m_currentDialog{ DialogType::None };
    int m_selectedSlot{ -1 };
    
    sf::RectangleShape m_dialogOverlay;
    sf::RectangleShape m_dialogBox;
    sf::Text m_dialogText;
    std::vector<std::unique_ptr<Button>> m_dialogButtons;
    
    bool m_needsUIUpdate{ false };
};

#endif