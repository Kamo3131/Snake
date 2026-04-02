#include <ResourceManager.hpp>

ResourceManager::ResourceManager() : textures() {}
sf::Texture& ResourceManager::getTexture(std::string path) {
    auto& pairFound = textures.find(path);
    if(pairFound != textures.end()){
        return pairFound->second;
    } else {
        sf::Texture& texture = textures[path];
        texture.loadFromFile(path);
        return texture;
    }
}

sf::Font& ResourceManager::getFont(std::string path) {
    std::map<std::string,sf::Font>::iterator& pairFound = fonts.find(path);
    if(pairFound != fonts.end()) {
        return pairFound->second;
    } else {
        sf::Font& font = fonts[path];
        font.openFromFile(path);
        return font;
    }
}

sf::SoundBuffer& ResourceManager::getSound(std::string path) {
    auto& pairFound = sounds.find(path);
    if(pairFound != sounds.end()) {
        return pairFound->second;
    } else {
        sf::SoundBuffer& sound = sounds[path];
        sound.loadFromFile(path);
        return sound;
    }
}