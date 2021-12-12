#pragma once
class MazeCoordinate
{
private:
	int x, y;
public:
	MazeCoordinate(int x, int y);
	MazeCoordinate();
	~MazeCoordinate();

	bool operator ==(const MazeCoordinate& other) const
	{
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}

	bool operator !=(const MazeCoordinate& other) const
	{
		if (x != other.x || y != other.y)
			return true;
		else
			return false;
	}
	int getX() const {
		return x;
	}

	int getY() const {
		return y;
	}

	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}
};



