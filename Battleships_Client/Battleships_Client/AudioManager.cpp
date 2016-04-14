#include "AudioManager.h"

AudioManager::AudioManager()
{
	connectionSoundBuffer = createSoundBuffer();
	connectionSound = createSound();
	shotSoundBuffer = createSoundBuffer();
	shotSound = createSound();
	chatPingSoundBuffer = createSoundBuffer();
	chatPingSound = createSound();
	music = new sf::Music;
}

AudioManager::~AudioManager()
{

}

void AudioManager::loadSoundFromFile(/*std::ifstream m_dataFile*/)
{
	//m_dataFile.open("AudioDatafile");
	//m_dataFile >> connectionSoundFile;
	//m_dataFile.close();
	connectionSoundFile = "connectionSound.wav";
	shotSoundFile = "Shot.wav";
	seaString = "Sea.wav";
	chatPingSoundFile = "ping.wav";
}

sf::SoundBuffer* AudioManager::createSoundBuffer()
{
	return new sf::SoundBuffer;
}

sf::Sound* AudioManager::createSound()
{
	return new sf::Sound;
}

void AudioManager::loadSound()
{
	music->openFromFile(seaString);
	connectionSoundBuffer->loadFromFile(connectionSoundFile);
	connectionSound->setBuffer(*connectionSoundBuffer);

	shotSoundBuffer->loadFromFile(shotSoundFile);
	shotSound->setBuffer(*shotSoundBuffer);

	chatPingSoundBuffer->loadFromFile(chatPingSoundFile);
	chatPingSound->setBuffer(*chatPingSoundBuffer);
}