#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "AnimationData.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

class Animator {
public:
    Animator() = default;

    void addAnimation(const std::string& name, const AnimationData& data) {
        m_animations[name] = data;
    }

    void play(const std::string& name) {
        if (m_currentAnimation == name) return;
        if (m_animations.find(name) != m_animations.end()) {
            m_currentAnimation = name;
            m_currentFrame = 0;
            m_elapsedTime = 0.0f;
            m_isPlaying = true;
        }
    }

    void update(float dt, sf::Sprite& targetSprite) {
        if (!m_isPlaying || m_currentAnimation.empty()) return;

        const auto& anim = m_animations[m_currentAnimation];
        m_elapsedTime += dt;

        if (m_elapsedTime >= anim.frameDuration) {
            m_elapsedTime -= anim.frameDuration;

            if (m_currentFrame + 1 < anim.frames.size()) {
                m_currentFrame++;
            } else if (anim.loop) {
                m_currentFrame = 0;
            } else {
                m_isPlaying = false;
            }
        }

        targetSprite.setTextureRect(anim.frames[m_currentFrame]);
    }

private:
    std::unordered_map<std::string, AnimationData> m_animations;
    std::string m_currentAnimation{ "" };
    size_t m_currentFrame{ 0 };
    float m_elapsedTime{ 0.0f };
    bool m_isPlaying{ false };
};

#endif