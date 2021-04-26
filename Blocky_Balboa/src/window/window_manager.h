#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <array>

#include "../cece_clock.h"
#include "event_class.h"

class Window
{
public:

	//Colors enum
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

	//Constructors
	//realistically one should take context settings, too bad!
	Window();
	Window(const Window& otherWindow) = delete;
	~Window() { glfwDestroyWindow(m_WindowID); glfwTerminate(); }

	//ID getter for functions that are not encapsulated yet
	inline GLFWwindow* getWindowID() { return m_WindowID; }

	//looping functionality
	void setFaceCullingCW() const;
	void setFaceCullingCCW() const;
	void prepareDraw();
	void swapBuffers();	
	inline bool isOpen() { return !glfwWindowShouldClose(m_WindowID); };
	inline void setSize() { glViewport(0, 0, m_width, m_height); }
	inline void close() { glfwSetWindowShouldClose(m_WindowID, 1); }
	inline double getCursorChangeX() { return cursor_dxpos; }
	inline double getCursorChangeY() { return cursor_dypos; }

public:
	bool isPressed[(uint32_t)Event::Key::Total_Number];
	

private:
	void init();
	void setCallbaks();

	void updateFPSCounter();
	void clear(Color color = Color::NONE);

	static void glfw_error_callback(int error, const char* description);
	static void glfw_window_size_callback(GLFWwindow* window, int width, int height);
	static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

private:
	GLFWwindow* m_WindowID;
	cece::Clock m_clock;

	int m_width, m_height;
	double cursor_dxpos, cursor_dypos;
};

void ShowConsole(bool show = true);

