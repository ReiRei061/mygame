#include "core/FontManager.hpp"
#include <iostream>
#include <stdexcept>

bool FontManager::loadFont(const std::string& id, const std::string& filename) {
    if (hasFont(id)) {
        return true;
    }

    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
        std::cerr << "[ERROR] FontManager: No se pudo cargar la fuente -> " << filename << "\n";
        return false;
    }

    m_fonts[id] = std::move(font);
    return true;
}

const sf::Font& FontManager::getFont(const std::string& id) const {
    auto it = m_fonts.find(id);
    if (it == m_fonts.end()) {
        throw std::runtime_error("[ERROR] FontManager: Se intento acceder a una fuente no cargada -> " + id);
    }
    return *it->second;
}

bool FontManager::hasFont(const std::string& id) const {
    return m_fonts.find(id) != m_fonts.end();
}

void FontManager::clear() {
    m_fonts.clear();
}