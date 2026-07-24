#include "AudioManager.hpp"
#include <iostream>
#include <stdexcept>

bool AudioManager::loadSound(const std::string& id, const std::string& filename) {
    if (hasSound(id)) {
        return true;
    }

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filename)) {
        std::cerr << "[ERROR] AudioManager: No se pudo cargar el archivo de audio -> " << filename << "\n";
        return false;
    }

    m_sounds[id] = std::move(buffer);
    return true;
}

const sf::SoundBuffer& AudioManager::getSound(const std::string& id) const {
    auto it = m_sounds.find(id);
    if (it == m_sounds.end()) {
        throw std::runtime_error("[ERROR] AudioManager: Se intento acceder a un sonido no cargado -> " + id);
    }
    return *it->second;
}

bool AudioManager::hasSound(const std::string& id) const {
    return m_sounds.find(id) != m_sounds.end();
}

void AudioManager::clear() {
    m_sounds.clear();
}