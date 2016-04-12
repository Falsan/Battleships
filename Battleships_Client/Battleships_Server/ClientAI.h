#pragma once
#include "Client.h"
#include "Board.h"


class AIClient : public ServerClient
{
public:
	AIClient(Board* _inBoard,int difficulty);
	~AIClient();

	int AIShoot();



};