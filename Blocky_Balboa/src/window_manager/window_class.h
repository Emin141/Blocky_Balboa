#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdio>
#include <array>

#include "event_class.h"

namespace cece
{
	class Window
	{
	public:
		enum class Color
		{
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

		//need to take care of context settings input
		Window() = delete;
		Window(
			int _width = 800,
			int _height = 600,
			const std::string _title = "Default window",
			bool fullscreen = false);
		Window(const Window &otherWindow) = delete;
		~Window()
		{
			glfwDestroyWindow(m_WindowID);
			glfwTerminate();
		}

		//ID getter for functions that are not encapsulated yet
		inline GLFWwindow *getWindowID() const { return m_WindowID; }

		//looping functionality
		void setFaceCullingCW() const;
		void setFaceCullingCCW() const;
		void prepareDraw() const;
		void swapBuffers() const;
		void pollEvents() const;
		inline bool isOpen() const { return !glfwWindowShouldClose(m_WindowID); };
		inline void setSize() const { glViewport(0, 0, m_width, m_height); }
		inline void close() const { glfwSetWindowShouldClose(m_WindowID, 1); }
		inline float getCursorChangeX() { return cursor_dxpos; }
		inline float getCursorChangeY() { return cursor_dypos; }
		inline bool keyIsPressed(Event::Key key) { return isPressed[(uint32_t)key]; }
		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

	private:
		void init(float _width, float _height, const std::string &_title, bool fullscreen);
		void setCallbaks();

		void updateFPSCounter() const;
		void clear(Color color = Color::NONE) const;

		bool isPressed[Event::Key::Total_Number];
		static void glfw_error_callback(int error, const char *description);
		static void glfw_window_size_callback(GLFWwindow *window, int width, int height);
		static void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

	private:
		GLFWwindow *m_WindowID;

		int m_width, m_height;
		float cursor_dxpos, cursor_dypos;
	};

	void show_console_window(bool show = true);
}