#ifndef CONFIG_SYSTEM_HPP
#define CONFIG_SYSTEM_HPP

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct GameConfig {
    bool fullscreen{ false };
    int targetFPS{ 60 }; // Options: 30, 60, 120, 0 (Unlimited/VSync)
    bool vsync{ true };
    float masterVolume{ 100.0f };
    float musicVolume{ 80.0f };
    float sfxVolume{ 100.0f };
};

class ConfigSystem {
public:
    static bool loadConfig(GameConfig& config) {
        std::ifstream file("config.json");
        if (!file.is_open()) {
            saveConfig(config); // Crear archivo por defecto si no existe
            return false;
        }

        json j;
        file >> j;
        config.fullscreen = j.value("fullscreen", false);
        config.targetFPS = j.value("target_fps", 60);
        config.vsync = j.value("vsync", true);
        config.masterVolume = j.value("master_volume", 100.0f);
        config.musicVolume = j.value("music_volume", 80.0f);
        config.sfxVolume = j.value("sfx_volume", 100.0f);
        return true;
    }

    static bool saveConfig(const GameConfig& config) {
        json j;
        j["fullscreen"] = config.fullscreen;
        j["target_fps"] = config.targetFPS;
        j["vsync"] = config.vsync;
        j["master_volume"] = config.masterVolume;
        j["music_volume"] = config.musicVolume;
        j["sfx_volume"] = config.sfxVolume;

        std::ofstream file("config.json");
        if (!file.is_open()) return false;
        file << j.dump(4);
        return true;
    }
};

#endif