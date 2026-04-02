#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceManager
{
public:
        ResourceManager();
        sf::Texture& getTexture(std::string path);
        sf::Font& getFont(std::string path);
        sf::SoundBuffer& getSound(std::string path);
private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
        std::map<std::string, sf::SoundBuffer> sounds;
};