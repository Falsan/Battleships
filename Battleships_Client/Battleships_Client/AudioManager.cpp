#include "AudioManager.h"

sf::SoundBuffer* AudioManager::createSoundBuffer() 
{
	//auto HOLD = new sf::SoundBuffer;
	//m_soundFiles.push_back(std::pair<HOLD, >)
	//return HOLD;
}

sf::Sound* AudioManager::createSounds()
{
	auto HOLD = new sf::Sound;
	m_sounds.push_back(HOLD);
	return HOLD;
}

void AudioManager::setSoundBuffers(std::vector<std::pair<sf::SoundBuffer, std::string>> m_soundFiles)
{
	for (auto iter = m_soundFiles.begin(); iter != m_soundFiles.end(); iter++)
	{
		(*iter).first.loadFromFile((*iter).second);
	}
}