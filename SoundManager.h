#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <map>

using namespace std;
using namespace sf;

class SoundManager
{
public:
    void loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
private:
    map<std::string, sf::SoundBuffer> buffers;
    map<std::string, sf::Sound> sounds;
};

