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

	sf::SoundBuffer* chatPingSoundBuffer;
	sf::Sound* chatPingSound;
	std::string chatPingSoundFile;

	sf::SoundBuffer* shotSoundBuffer;
	sf::Sound* shotSound;
	std::string shotSoundFile;

	sf::Music* music;
	std::string seaString;

protected:

private:
	


};