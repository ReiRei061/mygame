#ifndef ANIMATION_DATA_HPP
#define ANIMATION_DATA_HPP

#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>

struct AnimationData {
    std::string name;
    std::vector<sf::IntRect> frames;
    float frameDuration{ 0.1f }; // Tiempo por cuadro en segundos
    bool loop{ true };
};

#endif