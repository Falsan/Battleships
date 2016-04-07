#pragma once

class Cell
{
public:
	Cell() = default;
	~Cell() = default;

	int getType() { return type; };
	void setType(int thisSetType) { type = thisSetType; };
protected:

private:

	int type = 0;
};