#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class TextureManager {
public:
    TextureManager() = default;
    ~TextureManager() = default;

    // Deshabilitar copia para garantizar control único de memoria
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    // Carga una textura desde disco y la asocia a una clave única (id)
    bool loadTexture(const std::string& id, const std::string& filename);

    // Obtiene una referencia constante a la textura cargada
    const sf::Texture& getTexture(const std::string& id) const;

    // Verifica si la textura ya existe en el mapa
    bool hasTexture(const std::string& id) const;

    // Libera todas las texturas de la memoria
    void clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};

#endif // TEXTUREMANAGER_HPP