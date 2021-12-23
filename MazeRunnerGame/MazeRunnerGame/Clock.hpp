#pragma once
#include <time.h>
#include <stdint.h>
#include <string>
#include <sstream>

class MyClock
{
private:
	uint32_t m_CDTime;
	time_t m_StartTime;

public:
	void start();
	bool isOver();

public:
	uint32_t getCurrentCDTime();
	uint32_t getRunningTime();
	void setCDTime(uint32_t time);
	std::string getCDTime();
};

