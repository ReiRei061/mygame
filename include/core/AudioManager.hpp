#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class AudioManager {
public:
    AudioManager() = default;
    ~AudioManager() = default;

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    // Carga un buffer de sonido en memoria (para efectos como disparos, saltos, clics)
    bool loadSound(const std::string& id, const std::string& filename);
    const sf::SoundBuffer& getSound(const std::string& id) const;
    bool hasSound(const std::string& id) const;
    void clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_sounds;
};

#endif // AUDIOMANAGER_HPP