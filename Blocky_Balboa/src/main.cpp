#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window_manager.h"
#include "shader_manager.h"
#include "logger.h"
#include "cece_clock.h"
#include "cece_math.h"
#include "render_models/terrain.h"
#include "render_models/blocky.h"
#include "render_models/blocky_balboa.h"

float g_deltaTime;

int g_gl_width = 800;
int g_gl_height = 500;

int main() {
	ShowConsole();
	Window window;

	BlockyBalboa blocky_balboa;

	Blocky blocky_1;
	blocky_1.accessProgram()->setUniform("mvp", blocky_balboa.getMVP().c_arr());
	blocky_1.setWorldPosition({ 0.0f, 0.0f, -10.0f });

	Terrain terrain;
	terrain.accessProgram()->setUniform("mvp", blocky_balboa.getMVP().c_arr());

	cece::Clock Time;

	cece::Vector3 blocky_position = { 0, 0, 0 };

	while (window.isOpen()) {
		g_deltaTime = Time.deltaTime();

		window.updateFPSCounter();
		window.setSize(g_gl_width, g_gl_height);
		window.clear();

		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_W)) blocky_balboa.moveForward();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_S)) blocky_balboa.moveBackward();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_D)) blocky_balboa.moveRight();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_A)) blocky_balboa.moveLeft();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_SPACE)) blocky_balboa.moveUp();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_LEFT_SHIFT)) blocky_balboa.moveDown();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_E)) blocky_balboa.yawRight();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_Q)) blocky_balboa.yawLeft();
		/*if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_UP)) blocky_balboa.accessCamera()->pitchUp();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_DOWN)) blocky_balboa.accessCamera()->pitchDown();*/

		terrain.accessProgram()->updateUniform("mvp", blocky_balboa.getMVP().c_arr());
		terrain.draw();

		blocky_balboa.draw();

		blocky_1.accessProgram()->updateUniform("mvp", blocky_balboa.getMVP().c_arr());
		blocky_1.draw();

		window.swapBuffers();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.getWindowID(), 1);
		}

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}