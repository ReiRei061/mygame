#include "states/SelectSlotState.hpp"
#include "states/SelectDifficultyState.hpp"
#include "states/PlayState.hpp"
#include "states/MainMenuState.hpp"
#include "core/SaveSystem.hpp"
#include <iostream>

SelectSlotState::SelectSlotState(StateManager& stateManager, TextureManager& textureManager, 
                                 FontManager& fontManager, AudioManager& audioManager, sf::RenderWindow& window)
    : m_stateManager(stateManager), 
      m_textureManager(textureManager), 
      m_fontManager(fontManager), 
      m_audioManager(audioManager), 
      m_window(window),
      m_font(m_fontManager.getFont("main_font")),
      m_needsRefresh(false) {

    initUI();
}

void SelectSlotState::initUI() {
    m_buttons.clear();
    m_deleteButtons.clear();

    float startY = 180.0f;
    float offsetY = 70.0f;

    for (int i = 1; i <= 3; ++i) {
        bool slotExists = SaveSystem::exists(i);
        std::string slotLabel = "Slot " + std::to_string(i) + ": ";
        
        SaveData data;
        if (slotExists && SaveSystem::loadGame(i, data)) {
            slotLabel += "Guardado (" + data.difficulty + ")";
        } else {
            slotLabel += "Vacio";
        }

        // --- 1. BOTÓN DE RANURA (Iniciar / Cargar) ---
        m_buttons.push_back(std::make_unique<Button>(
            sf::Vector2f(200.0f, startY + (i - 1) * offsetY),
            sf::Vector2f(340.0f, 55.0f),
            m_font, slotLabel, 16,
            [this, i, slotExists, data]() {
                if (slotExists) {
                    m_stateManager.changeState(std::make_unique<PlayState>(
                        m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window,
                        "Slot_" + std::to_string(i), data.difficulty
                    ));
                } else {
                    m_stateManager.changeState(std::make_unique<SelectDifficultyState>(
                        m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window,
                        "Slot_" + std::to_string(i)
                    ));
                }
            }
        ));

        // --- 2. BOTÓN "X" PARA BORRAR (Solo si el archivo existe) ---
        if (slotExists) {
            auto deleteBtn = std::make_unique<Button>(
                sf::Vector2f(555.0f, startY + (i - 1) * offsetY),
                sf::Vector2f(45.0f, 55.0f),
                m_font, "X", 18,
                [this, i]() {
                    SaveSystem::deleteSave(i);
                    this->m_needsRefresh = true;
                }
            );
            
            deleteBtn->setColors(sf::Color(180, 40, 40), sf::Color(220, 60, 60), sf::Color(140, 20, 20));
            m_deleteButtons.push_back(std::move(deleteBtn));
        }
    } // <-- Cierre del for

    // --- 3. BOTÓN VOLVER AL MENÚ PRINCIPAL ---
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 430.0f),
        sf::Vector2f(200.0f, 45.0f),
        m_font, "VOLVER", 16,
        [this]() {
            m_stateManager.changeState(std::make_unique<MainMenuState>(
                m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window
            ));
        }
    ));
}

void SelectSlotState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    // Usar handleEvent exacto de tu clase Button
    for (auto& button : m_buttons) {
        button->handleEvent(event, window);
    }

    for (auto& deleteBtn : m_deleteButtons) {
        deleteBtn->handleEvent(event, window);
    }
}

void SelectSlotState::update(float dt) {
    if (m_needsRefresh) {
        initUI();
        m_needsRefresh = false;
    }
}

void SelectSlotState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    for (auto& button : m_buttons) {
        button->render(window);
    }

    for (auto& deleteBtn : m_deleteButtons) {
        deleteBtn->render(window);
    }
}