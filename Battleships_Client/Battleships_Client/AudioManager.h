#pragma once
#include "Client.h"
#include <SFML\Audio.hpp>
#include <vector>
class AudioManager
{
public:
	AudioManager();
	~AudioManager() {	for (auto it = m_soundFiles.begin(); it != m_soundFiles.end(); it++) { delete (*it); }	};

	void loadSounds();
	void setSoundBuffers(std::vector<std::pair<sf::SoundBuffer, std::string>> m_soundFiles);

	sf::SoundBuffer* createSoundBuffer();
	sf::Sound* createSounds();

protected:

private:
	//std::vector<sf::SoundBuffer *> m_soundBuffers;
	std::vector<sf::Sound *> m_sounds;
	std::vector<std::pair<sf::SoundBuffer, std::string>> m_soundFiles;

	//sf::SoundBuffer;

};