#include "cece_clock.h"

using namespace cece;

float Clock::deltaTime() const
{
	static double previous_seconds = glfwGetTime();
	double current_seconds = glfwGetTime();
	double delta_time = current_seconds - previous_seconds;
	previous_seconds = current_seconds;
	return delta_time;
}
