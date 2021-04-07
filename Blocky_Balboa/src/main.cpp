#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window_manager.h"
#include "shader_manager.h"
#include "logger.h"
#include "cece_clock.h"
#include "cece_math.h"
#include "camera/cece_camera.h"
#include "render_models/terrain.h"
#include "render_models/blocky.h"

float g_deltaTime;

int g_gl_width = 800;
int g_gl_height = 500;

int main() {
	ShowConsole();
	Window window;

	cece::Camera camera;

	Blocky blocky;
	blocky.accessProgram()->setUniform("mvp", camera.getMVP().c_arr());

	Terrain terrain;
	terrain.accessProgram()->setUniform("mvp", camera.getMVP().c_arr());

	cece::Clock Time;

	while (window.isOpen()) {
		g_deltaTime = Time.deltaTime();

		window.updateFPSCounter();
		window.setSize(g_gl_width, g_gl_height);
		window.clear();

		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_W)) camera.moveForward();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_S)) camera.moveBackward();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_D)) camera.moveRight();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_A)) camera.moveLeft();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_SPACE)) camera.moveUp();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_LEFT_SHIFT)) camera.moveDown();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_E)) camera.yawRight();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_Q)) camera.yawLeft();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_UP)) camera.pitchUp();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_DOWN)) camera.pitchDown();

		terrain.accessProgram()->updateUniform("mvp", camera.getMVP().c_arr());
		terrain.draw();

		blocky.accessProgram()->updateUniform("mvp", camera.getMVP().c_arr());
		blocky.draw();

		window.swapBuffers();
		if (GLFW_PRESS == glfwGetKey(window.getWindowID(), GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.getWindowID(), 1);
		}

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}