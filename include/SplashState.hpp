#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include "State.hpp"
#include "StateManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include <SFML/Graphics.hpp>

class SplashState : public State {
public:
    SplashState(StateManager& stateManager, TextureManager& textureManager, FontManager& fontManager);
    ~SplashState() override = default;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& m_stateManager;
    TextureManager& m_textureManager;
    FontManager& m_fontManager;

    sf::Sprite m_logoSprite;
    sf::Text m_skipText;

    float m_timer{ 0.0f };
    const float m_duration{ 3.0f }; // Duración en segundos antes de pasar al menú automáticamente
    
    // Para hacer un efecto suave de entrada/salida (Fade In / Fade Out)
    float m_alpha{ 0.0f };

    void goToMainMenu();
};

#endif // SPLASHSTATE_HPP