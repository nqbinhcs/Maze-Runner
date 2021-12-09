#pragma once
class MazeCoordinate
{
	int x, y;
public:
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


