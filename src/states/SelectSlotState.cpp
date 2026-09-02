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
      m_needsRefresh(false),
      m_slotToDelete(-1) {

    // Overlay oscuro para la confirmación
    m_overlay.setSize(sf::Vector2f(800.0f, 600.0f));
    m_overlay.setFillColor(sf::Color(0, 0, 0, 190));

    initUI();
}

void SelectSlotState::initUI() {

    // Carga de Fondo
    m_textureManager.loadTexture("main_menu_bg", "assets/menus/menu01.png");
    m_backgroundSprite.setTexture(m_textureManager.getTexture("main_menu_bg"));

    sf::Vector2u textureSize = m_backgroundSprite.getTexture()->getSize();
    m_backgroundSprite.setScale(
        800.0f / static_cast<float>(textureSize.x),
        600.0f / static_cast<float>(textureSize.y)
    );

    m_buttons.clear();
    m_deleteButtons.clear();
    m_confirmButtons.clear();

    float startY = 160.0f;
    float offsetY = 75.0f;

    // Centrado absoluto del botón principal en pantalla (800px)
    float slotWidth = 360.0f;
    float deleteBtnWidth = 45.0f;
    float gap = 10.0f;
    float slotStartX = (800.0f - slotWidth) / 2.0f; // Exactamente 220.0px

    for (int i = 1; i <= 3; ++i) {
        bool slotExists = SaveSystem::exists(i);
        std::string slotLabel = "Slot " + std::to_string(i) + ": ";
        
        SaveData data;
        if (slotExists && SaveSystem::loadGame(i, data)) {
            slotLabel += "Guardado (" + data.difficulty + ")";
        } else {
            slotLabel += "Vacio";
        }

        // --- 1. BOTÓN DE RANURA (Centrado) ---
        m_buttons.push_back(std::make_unique<Button>(
            sf::Vector2f(slotStartX, startY + (i - 1) * offsetY),
            sf::Vector2f(slotWidth, 55.0f),
            m_font, slotLabel, 16,
            [this, i, slotExists, data]() {
                if (m_slotToDelete != -1) return;

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

        // --- 2. BOTÓN "X" (Ubicado a la derecha sin afectar el centrado) ---
        if (slotExists) {
            auto deleteBtn = std::make_unique<Button>(
                sf::Vector2f(slotStartX + slotWidth + gap, startY + (i - 1) * offsetY),
                sf::Vector2f(deleteBtnWidth, 55.0f),
                m_font, "X", 18,
                [this, i]() {
                    if (m_slotToDelete == -1) {
                        this->m_slotToDelete = i;
                    }
                }
            );
            
            deleteBtn->setColors(sf::Color(180, 40, 40), sf::Color(220, 60, 60), sf::Color(140, 20, 20));
            m_deleteButtons.push_back(std::move(deleteBtn));
        }
    }

    // --- 3. BOTÓN VOLVER ---
    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f(300.0f, 440.0f),
        sf::Vector2f(200.0f, 45.0f),
        m_font, "VOLVER", 16,
        [this]() {
            if (m_slotToDelete != -1) return;
            m_stateManager.changeState(std::make_unique<MainMenuState>(
                m_stateManager, m_textureManager, m_fontManager, m_audioManager, m_window
            ));
        }
    ));

    // --- 4. MODAL DE CONFIRMACIÓN ---
    m_confirmText.setFont(m_font);
    m_confirmText.setString("¿Seguro que deseas eliminar esta partida?");
    m_confirmText.setCharacterSize(20);
    m_confirmText.setFillColor(sf::Color::White);
    
    sf::FloatRect bounds = m_confirmText.getLocalBounds();
    m_confirmText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    m_confirmText.setPosition(400.0f, 250.0f);

    // Botón SÍ
    auto yesBtn = std::make_unique<Button>(
        sf::Vector2f(260.0f, 310.0f), sf::Vector2f(120.0f, 40.0f),
        m_font, "SI", 16,
        [this]() {
            if (m_slotToDelete != -1) {
                SaveSystem::deleteSave(m_slotToDelete);
                m_slotToDelete = -1;
                m_needsRefresh = true;
            }
        }
    );
    yesBtn->setColors(sf::Color(180, 40, 40), sf::Color(220, 60, 60), sf::Color(140, 20, 20));
    m_confirmButtons.push_back(std::move(yesBtn));

    // Botón NO
    auto noBtn = std::make_unique<Button>(
        sf::Vector2f(420.0f, 310.0f), sf::Vector2f(120.0f, 40.0f),
        m_font, "NO", 16,
        [this]() {
            m_slotToDelete = -1;
        }
    );
    m_confirmButtons.push_back(std::move(noBtn));
}

void SelectSlotState::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (m_slotToDelete != -1) {
        for (auto& btn : m_confirmButtons) {
            btn->handleEvent(event, window);
        }
        return;
    }

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

    window.draw(m_backgroundSprite);

    for (auto& button : m_buttons) {
        button->render(window);
    }

    for (auto& deleteBtn : m_deleteButtons) {
        deleteBtn->render(window);
    }

    if (m_slotToDelete != -1) {
        window.draw(m_overlay);
        window.draw(m_confirmText);
        for (auto& btn : m_confirmButtons) {
            btn->render(window);
        }
    }
}