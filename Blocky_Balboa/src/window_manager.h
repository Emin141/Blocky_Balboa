#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	enum class Color {
		NONE = -1,
		WHITE = 0,
		BLACK = 1,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA
	};

	Window(const bool fullscreen_enabled = false);
	Window(const Window& otherWindow) = delete;
	//Dodaj funkcionalnost da drkas opcije
	inline GLFWwindow* getWindowID() { return m_WindowID; }
	void updateFPSCounter();
	void setFaceCullingCW(bool set = true);
	void swapBuffers();
	void clear(Color color = Color::NONE);
	inline bool isOpen() { return !glfwWindowShouldClose(m_WindowID); };
	inline void setSize(int width, int height) { glViewport(0, 0, width, height); }

private:
	GLFWwindow* m_WindowID;
};

void ShowConsole(bool show = true);