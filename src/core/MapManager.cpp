#include "core/MapManager.hpp"
#include <iostream>

MapManager::MapManager(TextureManager& textureManager)
    : m_textureManager(textureManager) {}

void MapManager::loadMap(const std::string& mapName) {
    std::string filepath = "assets/maps/" + mapName + ".png";
    m_textureManager.loadTexture(mapName, filepath);

    if (m_textureManager.hasTexture(mapName)) {
        m_backgroundSprite.setTexture(m_textureManager.getTexture(mapName));
        
        // Ajustar la imagen al tamaño interno del juego (800x600)
        sf::Vector2u textureSize = m_backgroundSprite.getTexture()->getSize();
        m_backgroundSprite.setScale(
            800.0f / static_cast<float>(textureSize.x),
            600.0f / static_cast<float>(textureSize.y)
        );

        m_currentMap = mapName;
        std::cout << "[MapManager] Mapa cargado con exito: " << mapName << std::endl;
    } else {
        std::cerr << "[MapManager] Error: No se pudo cargar " << filepath << std::endl;
    }
}

void MapManager::render(sf::RenderWindow& window) {
    window.draw(m_backgroundSprite);
}