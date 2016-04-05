#pragma once
#include <string>
#include <chrono>

typedef  std::chrono::high_resolution_clock Clock;


class inputAction
{
public:
	inputAction() = default;
	~inputAction() = default;

	void setPlayerID(int _in) { PlayerID = _in; };
	void setActionID(int _in) { actionID = _in; };
	void setPos(int _in, int _in2) { pos.first = _in; pos.second = _in2; };
	void setMessage(std::string _in) { message = _in; };
	void setMenuAction(int _in) { menuAction = _in; };
	void setActionCompleate(bool _in) { actioncomplete = _in; }
	void setPlayerNickName(std::string _in) { PlayerNick = _in; }
	void setPongTime(std::chrono::high_resolution_clock::time_point _in) { pongTime = _in; }

	int getPlayerID() { return PlayerID; };
	int getActionID() { return actionID; };
	std::pair<int, int> getPos() { return pos; };
	std::string getMessage() { return message; };
	int getMenuAction() { return menuAction; };
	int getActionCompleate() { return actioncomplete; }
	std::string getPlayerNick() { return PlayerNick; }
	std::chrono::high_resolution_clock::time_point getPongTime() { return pongTime; }

private:

	std::chrono::high_resolution_clock::time_point pongTime;
	int PlayerID;
	std::string PlayerNick;
	int actionID;
	std::pair<int, int> pos;
	std::string message;
	int menuAction;
	bool actioncomplete = false;

};