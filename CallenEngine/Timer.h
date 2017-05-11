#pragma once
#include <ctime>

class Timer
{
private:
	float cur, prev;
public:
	float t;	//time in seconds since starting/constructor/declaration
	float dt;	//time in seconds btw 2 most recent updates
	float fps;	//measures 1/dt, approx immediate # of updates per second

	Timer();
	~Timer();

	void update();
};

