#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class MapManager {
public:
    explicit MapManager(TextureManager& textureManager);

    void loadMap(const std::string& mapName);
    void render(sf::RenderWindow& window);

    const std::string& getCurrentMap() const { return m_currentMap; }

private:
    TextureManager& m_textureManager;
    sf::Sprite m_backgroundSprite;
    std::string m_currentMap;
};

#endif // MAPMANAGER_HPP