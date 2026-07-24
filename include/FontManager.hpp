#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class FontManager {
public:
    FontManager() = default;
    ~FontManager() = default;

    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    bool loadFont(const std::string& id, const std::string& filename);
    const sf::Font& getFont(const std::string& id) const;
    bool hasFont(const std::string& id) const;
    void clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
};

#endif // FONTMANAGER_HPP