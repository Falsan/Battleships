#pragma once
#include "Client.h"
#include <SFML\Audio.hpp>
#include <vector>
#include <fstream>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void loadSound();
	//void setSoundBuffer(sf::SoundBuffer*);

	sf::SoundBuffer* createSoundBuffer();
	sf::Sound* createSound();
	void loadSoundFromFile(/*std::ifstream*/);

	sf::SoundBuffer* connectionSoundBuffer;
	sf::Sound* connectionSound;
	std::string connectionSoundFile;

protected:

private:
	


};