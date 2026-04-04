#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager() : textures() {}

sf::Texture& ResourceManager::getTexture(std::string path) {
    auto pairFound = textures.find(path);
    if(pairFound != textures.end()){
        return pairFound->second;
    } 
    
    sf::Texture& texture = textures[path];
    if (!texture.loadFromFile(path)) {
        std::cout << "Texture " << path << " not loaded correctly!\n";
    }
    return texture;
}

sf::Font& ResourceManager::getFont(std::string path) {
    std::map<std::string,sf::Font>::iterator pairFound = fonts.find(path);
    if(pairFound != fonts.end()) {
        return pairFound->second;
    } 
    sf::Font& font = fonts[path];
    if (!font.openFromFile(path)){
        std::cout << "Font " << path << " not loaded correctly!\n";
    }
    return font;
}

sf::SoundBuffer& ResourceManager::getSound(std::string path) {
    auto pairFound = sounds.find(path);
    if(pairFound != sounds.end()) {
        return pairFound->second;
    } 
    sf::SoundBuffer& sound = sounds[path];
    if(!sound.loadFromFile(path)) {
        std::cout << "Sound " << path << " not loaded correctly!\n";
    }
    return sound; 
}