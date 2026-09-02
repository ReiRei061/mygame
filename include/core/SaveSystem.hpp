#ifndef SAVE_SYSTEM_HPP
#define SAVE_SYSTEM_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Estructura contenedora de los datos de partida
struct SaveData {
    int slotId{ 1 };
    std::string difficulty{ "Normal" };
    std::string currentMap = "map01";
    float playerX{ 400.0f };
    float playerY{ 300.0f };
    // Aquí agregaremos el inventario más adelante
};

class SaveSystem {
public:
    // Comprueba si existe el archivo de un slot
    static bool exists(int slotIndex) {
        std::string filename = "saves/slot_" + std::to_string(slotIndex) + ".json";
        std::ifstream file(filename);
        return file.good();
    }

    // Guarda los datos en formato JSON
    static bool saveGame(int slotIndex, const SaveData& data) {
        std::string filename = "saves/slot_" + std::to_string(slotIndex) + ".json";
        
        json j;
        j["current_map"] = data.currentMap;
        j["slot_id"] = slotIndex;
        j["difficulty"] = data.difficulty;
        j["player_x"] = data.playerX;
        j["player_y"] = data.playerY;

        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << j.dump(4); // Sangría de 4 espacios
        return true;
    }

    // Carga los datos desde el JSON
    static bool loadGame(int slotIndex, SaveData& outData) {
        std::string filename = "saves/slot_" + std::to_string(slotIndex) + ".json";
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        json j;
        file >> j;

        outData.slotId = slotIndex;
        outData.currentMap = j.value("current_map", "map01");
        outData.difficulty = j.value("difficulty", "Normal");
        outData.playerX = j.value("player_x", 400.0f);
        outData.playerY = j.value("player_y", 300.0f);

        return true;
    }

    // Elimina el archivo físico de guardado
    static bool deleteSave(int slotIndex) {
        std::string filename = "saves/slot_" + std::to_string(slotIndex) + ".json";
        return (std::remove(filename.c_str()) == 0);
    }
};

#endif