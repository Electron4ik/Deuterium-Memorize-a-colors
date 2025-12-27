#include "SoundManager.h"

void SoundManager::loadSound(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Loading error " << filename << "\n";
        return;
    }
    buffers[name] = buffer; // Сохраняем буфер
    sounds[name].setBuffer(buffers[name]); // Создаём `sf::Sound`
}

void SoundManager::playSound(const std::string& name)
{
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    }
    else {
        std::cerr << "Sounds: " << name << " not found!\n";
    }
}
