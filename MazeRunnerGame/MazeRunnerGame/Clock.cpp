#include "Clock.hpp"
#include <iostream>

uint32_t MyClock::getRunningTimeInSec() {
	return difftime(time(0), m_StartTime);
}

uint32_t MyClock::getCurrentCDTime() {
	//std::cout << getRunningTimeInSec() << std::endl;
	return (m_CDTime > getRunningTimeInSec() ? (m_CDTime - getRunningTimeInSec()) : 0);
}

void MyClock::start() {
	m_StartTime = time(0);
}

bool MyClock::isOver() {
	return getRunningTimeInSec() > m_CDTime;
}

void MyClock::setCDTime(uint32_t time) {
	m_CDTime = time;
}

std::string MyClock::getCDTime()
{
	//std::cout << getCurrentCDTime() << std::endl;
	std::stringstream writer("");

	uint32_t time = getCurrentCDTime();

	uint32_t hour = time / 3600;
	time -= hour * 3600;
	uint32_t min = time / 60;
	time -= min * 60;
	uint32_t sec = time;

	if (hour > 0) {
		if (hour < 10)
			writer << 0 << hour << ".";
		else
			writer << hour << ".";
	}

	if (min < 10)
		writer << 0 << min << ".";
	else
		writer << min << ".";

	if (sec < 10)
		writer << 0 << sec;
	else
		writer << sec;

	return writer.str();
}