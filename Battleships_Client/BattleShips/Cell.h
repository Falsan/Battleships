#pragma once

class Cell
{
public:
	Cell() = default;
	~Cell() = default;

	int getType() { return type; };
	void setType(int thisSetType) { type = thisSetType; };

	float getShotChance() { return shotChance; }
	void setShotChance(float _in) { shotChance = _in; }
protected:

private:
	float shotChance=0;
	int type = 0;
};