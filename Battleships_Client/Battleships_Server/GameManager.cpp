#include "GameManager.h"

gameManager::gameManager()
{
	//swap for smart pointer 
	m_gameBoard = new board;
}

gameManager::~gameManager()
{
	delete m_gameBoard;
}