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

private:
	uint32_t getRunningTime();
	uint32_t getCurrentCDTime();
	
public:
	void start();
	bool isOver();

public:
	void setCDTime(uint32_t time);
	std::string getCDTime();
};

