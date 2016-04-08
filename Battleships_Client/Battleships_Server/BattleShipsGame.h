#pragma once
#include "Game.h"
#include "Client.h"

class BattleShipsGame : public GameBase
{
public:
	BattleShipsGame(Client* _playerOne, Client * _playerTwo);
	~BattleShipsGame() = default;

	virtual void update() override;

	virtual void input(int _in) override;
	virtual int outPut() override;
	
private:
};