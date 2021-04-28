#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdio>
#include <array>

#include "event_class.h"

namespace cece {
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
		Window(int _width, int _height, const std::string& _title, bool fullscreen);
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
		inline float getCursorChangeX() { return cursor_dxpos; }
		inline float getCursorChangeY() { return cursor_dypos; }
		inline bool keyIsPressed(Event::Key key) { return isPressed[(uint32_t)key]; }
		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

	private:
		void init(float _width, float _height, const std::string& _title, bool fullscreen);
		void setCallbaks();

		void updateFPSCounter();
		void clear(Color color = Color::NONE);

		bool isPressed[(uint32_t)Event::Key::Total_Number];
		static void glfw_error_callback(int error, const char* description);
		static void glfw_window_size_callback(GLFWwindow* window, int width, int height);
		static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	private:
		GLFWwindow* m_WindowID;

		int m_width, m_height;
		float cursor_dxpos, cursor_dypos;
	};

	void ShowConsole(bool show = true);
}