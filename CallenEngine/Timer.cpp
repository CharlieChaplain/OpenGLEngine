#include "Timer.h"

#include "GLFW/glfw3.h"
#include <iostream>

Timer::Timer()
{
	prev = cur = glfwGetTime();
	t = dt = fps = 0;
}


Timer::~Timer()
{
}

void Timer::update()
{
	prev = cur;
	cur = glfwGetTime();
	dt = cur - prev;
	t += dt;
	fps = 1 / dt;
	std::cout << fps << '\n';
}
