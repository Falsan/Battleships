#pragma once
#include "Game.h"
#include "Client.h"


class BattleShipsGame : public GameBase
{
public:
	BattleShipsGame(ServerClient* _playerOne, ServerClient * _playerTwo);
	~BattleShipsGame() = default;

	virtual bool update(sf::Packet _inPacket, ServerClient * _inClient) override;

	virtual void input(int _in) override;
	virtual int outPut() override;
	
private:
};