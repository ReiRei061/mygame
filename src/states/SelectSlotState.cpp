#include "states/SelectSlotState.hpp"
#include "states/PlayState.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

SelectSlotState::SelectSlotState(StateManager& stateManager, TextureManager& textureManager, FontManager& fontManager)
    : m_stateManager(stateManager), m_textureManager(textureManager), m_fontManager(fontManager) {
    
    m_dialogOverlay.setSize(sf::Vector2f(800.0f, 600.0f));
    m_dialogOverlay.setFillColor(sf::Color(0, 0, 0, 150));

    m_dialogBox.setSize(sf::Vector2f(420.0f, 220.0f));
    m_dialogBox.setFillColor(sf::Color(35, 45, 35, 245));
    m_dialogBox.setOutlineColor(sf::Color(180, 120, 50));
    m_dialogBox.setOutlineThickness(3.0f);
    m_dialogBox.setPosition(190.0f, 190.0f);

    if (m_textureManager.hasTexture("main_menu_bg")) {
        m_backgroundSprite.setTexture(m_textureManager.getTexture("main_menu_bg"));
    }

    updateSlotUI();
}

void SelectSlotState::updateSlotUI() {
    m_slotButtons.clear();
    m_deleteButtons.clear();

    const sf::Font& font = m_fontManager.getFont("main_font");

    // Configuración del Título
    m_titleText.setFont(font);
    m_titleText.setString("SELECCIONAR PARTIDA");
    m_titleText.setCharacterSize(36);
    m_titleText.setFillColor(sf::Color(255, 235, 180));
    m_titleText.setOutlineColor(sf::Color(35, 25, 15, 220));
    m_titleText.setOutlineThickness(2.0f);
    sf::FloatRect bounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    m_titleText.setPosition(400.0f, 80.0f);

    float slotWidth = 300.0f;
    float slotHeight = 60.0f;
    float slotX = (800.0f - slotWidth) / 2.0f;

    for (int i = 0; i < 3; ++i) {
        int slotNum = i + 1;
        bool hasSave = SaveSystem::exists(slotNum);
        
        std::string slotLabel = "SLOT " + std::to_string(slotNum);
        if (hasSave) {
            SaveData data;
            SaveSystem::loadGame(slotNum, data);
            slotLabel += " (" + data.difficulty + ")";
        } else {
            slotLabel += " (Vacio)";
        }

        // Botón principal de Slot
        m_slotButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(slotX, 160.0f + i * 80.0f), sf::Vector2f(slotWidth, slotHeight),
            font, slotLabel, 18,
            [this, slotNum, hasSave]() {
                if (hasSave) {
                    openDialog(DialogType::ConfirmContinue, slotNum);
                } else {
                    openDialog(DialogType::DifficultySelection, slotNum);
                }
            }
        ));

        // Botón 'X' para eliminar
        if (hasSave) {
            m_deleteButtons.push_back(std::make_unique<Button>(
                sf::Vector2f(slotX + slotWidth + 10.0f, 160.0f + i * 80.0f + 12.0f),
                sf::Vector2f(35.0f, 35.0f),
                font, "X", 16,
                [this, slotNum]() {
                    openDialog(DialogType::ConfirmDelete, slotNum);
                }
            ));
        }
    }

    // Botón Volver
    m_backButton = std::make_unique<Button>(
        sf::Vector2f(50.0f, 510.0f), sf::Vector2f(140.0f, 40.0f),
        font, "VOLVER", 18,
        [this]() { m_stateManager.popState(); }
    );
}

void SelectSlotState::openDialog(DialogType type, int slotIndex) {
    m_currentDialog = type;
    m_selectedSlot = slotIndex;
    m_dialogButtons.clear();

    const sf::Font& font = m_fontManager.getFont("main_font");

    if (type == DialogType::DifficultySelection) {
        m_dialogText.setFont(font);
        m_dialogText.setString("Seleccionar Dificultad");
        m_dialogText.setCharacterSize(20);
        m_dialogText.setFillColor(sf::Color::White);
        m_dialogText.setPosition(275.0f, 205.0f);

        // FACIL
        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(220.0f, 250.0f), sf::Vector2f(110.0f, 35.0f),
            font, "FACIL", 14,
            [this]() {
                SaveData data{ m_selectedSlot, "FACIL" };
                SaveSystem::saveGame(m_selectedSlot, data);
                m_needsUIUpdate = true;
                m_stateManager.pushState(std::make_unique<PlayState>(m_stateManager, m_fontManager, data));
            }
        ));

        // NORMAL
        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(345.0f, 250.0f), sf::Vector2f(110.0f, 35.0f),
            font, "NORMAL", 14,
            [this]() {
                SaveData data{ m_selectedSlot, "NORMAL" };
                SaveSystem::saveGame(m_selectedSlot, data);
                m_needsUIUpdate = true;
                m_stateManager.pushState(std::make_unique<PlayState>(m_stateManager, m_fontManager, data));
            }
        ));

        // DIFICIL
        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(470.0f, 250.0f), sf::Vector2f(110.0f, 35.0f),
            font, "DIFICIL", 14,
            [this]() {
                SaveData data{ m_selectedSlot, "DIFICIL" };
                SaveSystem::saveGame(m_selectedSlot, data);
                m_needsUIUpdate = true;
                m_stateManager.pushState(std::make_unique<PlayState>(m_stateManager, m_fontManager, data));
            }
        ));

        // CANCELAR
        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(335.0f, 330.0f), sf::Vector2f(130.0f, 35.0f),
            font, "CANCELAR", 14,
            [this]() { m_needsUIUpdate = true; }
        ));

    } else if (type == DialogType::ConfirmContinue) {
        m_dialogText.setFont(font);
        m_dialogText.setString("Desea continuar partida?");
        m_dialogText.setCharacterSize(22);
        m_dialogText.setFillColor(sf::Color::White);
        m_dialogText.setPosition(250.0f, 220.0f);

        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(240.0f, 320.0f), sf::Vector2f(130.0f, 40.0f),
            font, "SI", 18,
            [this]() {
                SaveData data;
                SaveSystem::loadGame(m_selectedSlot, data);
                m_needsUIUpdate = true;
                m_stateManager.pushState(std::make_unique<PlayState>(m_stateManager, m_fontManager, data));
            }
        ));

        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(430.0f, 320.0f), sf::Vector2f(130.0f, 40.0f),
            font, "NO", 18,
            [this]() { m_needsUIUpdate = true; }
        ));

    } else if (type == DialogType::ConfirmDelete) {
        m_dialogText.setFont(font);
        m_dialogText.setString("Seguro de borrar partida?");
        m_dialogText.setCharacterSize(22);
        m_dialogText.setFillColor(sf::Color(255, 100, 100));
        m_dialogText.setPosition(230.0f, 220.0f);

        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(240.0f, 320.0f), sf::Vector2f(130.0f, 40.0f),
            font, "SI", 18,
            [this]() {
                SaveSystem::deleteSave(m_selectedSlot);
                m_needsUIUpdate = true;
            }
        ));

        m_dialogButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(430.0f, 320.0f), sf::Vector2f(130.0f, 40.0f),
            font, "NO", 18,
            [this]() { m_needsUIUpdate = true; }
        ));
    }
}

void SelectSlotState::closeDialog() {
    m_currentDialog = DialogType::None;
    m_selectedSlot = -1;
    m_dialogButtons.clear();
}

void SelectSlotState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        if (m_currentDialog != DialogType::None) {
            closeDialog();
        } else {
            m_stateManager.popState();
        }
        return;
    }

    if (m_currentDialog != DialogType::None) {
        for (auto& btn : m_dialogButtons) {
            btn->handleEvent(event, window);
        }
        return;
    }

    for (auto& btn : m_slotButtons) {
        btn->handleEvent(event, window);
    }
    for (auto& btn : m_deleteButtons) {
        btn->handleEvent(event, window);
    }
    m_backButton->handleEvent(event, window);
}

void SelectSlotState::update(float dt) {
    // Cierre seguro diferido de diálogos y refresco de interfaz
    if (m_needsUIUpdate) {
        closeDialog();
        updateSlotUI();
        m_needsUIUpdate = false;
    }
}

void SelectSlotState::render(sf::RenderWindow& window) {
    window.draw(m_backgroundSprite);
    window.draw(m_titleText);

    for (auto& btn : m_slotButtons) {
        btn->render(window);
    }
    for (auto& btn : m_deleteButtons) {
        btn->render(window);
    }
    m_backButton->render(window);

    if (m_currentDialog != DialogType::None) {
        window.draw(m_dialogOverlay);
        window.draw(m_dialogBox);
        window.draw(m_dialogText);
        for (auto& btn : m_dialogButtons) {
            btn->render(window);
        }
    }
}