#pragma once
#include "MazeObject.hpp"

#define IMG_TRAP_INACTIVE "Images/SpikeTrapInactive.png"
#define IMG_TRAP_ACTIVE "Images/SpikeTrapActive.png"

class MazeTrap : public MazeObject
{
private:
	int maxTrapTime;
	int curTrapTime;
	static bool loadPlayerImages;
	static sf::Image trapActiveTexture;
	static sf::Image trapInactiveTexture;
private:
	bool isActive;
public:

	MazeTrap(MazeCoordinate pos, float xOffset, float yOffset, float width, float height);
	~MazeTrap();

	bool getActive() {
		return isActive;
	}
	//Increments trap time and checks if trap state must change each cycle
	void NextCycle();
	//Sets trap texture based off of current trap state
	void SetTrapTexture();
};


