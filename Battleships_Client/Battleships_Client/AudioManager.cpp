#include "AudioManager.h"

AudioManager::AudioManager()
{
	connectionSoundBuffer = createSoundBuffer();
	connectionSound = createSound();
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
	connectionSoundBuffer->loadFromFile(connectionSoundFile);
	connectionSound->setBuffer(*connectionSoundBuffer);
}