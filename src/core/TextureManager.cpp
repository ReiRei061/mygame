#include "core/TextureManager.hpp"
#include <iostream>
#include <stdexcept>

bool TextureManager::loadTexture(const std::string& id, const std::string& filename) {
    // Si la textura ya fue cargada anteriormente, no volvemos a leer el disco
    if (hasTexture(id)) {
        return true;
    }

    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "[ERROR] TextureManager: No se pudo cargar el archivo -> " << filename << "\n";
        return false;
    }

    m_textures[id] = std::move(texture);
    return true;
}

const sf::Texture& TextureManager::getTexture(const std::string& id) const {
    auto it = m_textures.find(id);
    if (it == m_textures.end()) {
        throw std::runtime_error("[ERROR] TextureManager: Se intento acceder a una textura no cargada -> " + id);
    }
    return *it->second;
}

bool TextureManager::hasTexture(const std::string& id) const {
    return m_textures.find(id) != m_textures.end();
}

void TextureManager::clear() {
    m_textures.clear();
}