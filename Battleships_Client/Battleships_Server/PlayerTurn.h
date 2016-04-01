#pragma once
#include <vector>

class PlayerTurn
{
public:
	std::pair<int, int> getShot() { return shot; }
	bool getActedUpon() { return actedUpon; }

	void setShot(std::pair <int, int> _in) { shot = _in; }
	void setActedUpon(bool _in) { actedUpon = _in; }
private:
	std::pair<int, int> shot;
	bool actedUpon = false;
};