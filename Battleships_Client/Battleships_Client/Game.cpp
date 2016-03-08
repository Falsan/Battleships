#include "Game.h"

Game::Game()
{
	//all initial creation for the game goes here
}

Game::~Game()
{
	//all deletion goes here
}

void Game::setup()
{
	//threads launch here

	//any leftover variables are set up

	//begins update loop
}

void Game::update()
{
	//update the game logic from the last server data

	//put that to the screen using the UI manager

	//request any input from the input manager

	//if needed, pass the input to the packet manager to be sent to the server
}

void Game::render()
{
	//use the ui manager to render everything to screen
}