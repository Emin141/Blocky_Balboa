#include <iostream>

#include "window_class.h"
#include "../logger/logger.h"

namespace cece
{
	void Window::setCallbaks()
	{
		glfwSetErrorCallback(glfw_error_callback);
		glfwSetWindowSizeCallback(m_WindowID, glfw_window_size_callback);
		glfwSetKeyCallback(m_WindowID, glfw_key_callback);
		glfwSetCursorPosCallback(m_WindowID, glfw_cursor_position_callback);
	}

	void Window::glfw_error_callback(int error, const char *description)
	{
		gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
	}

	void Window::glfw_window_size_callback(GLFWwindow *window, int width, int height)
	{
		Window *ptrWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

		ptrWindow->m_width = width;
		ptrWindow->m_height = height;
		ptrWindow->setSize();
	}

	void Window::glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		Window *ptrWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

		using Key = Event::Key;

		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				ptrWindow->isPressed[Key::Escape] = true; break;
			case GLFW_KEY_Q:
				ptrWindow->isPressed[Key::Q] = true; break;
			case GLFW_KEY_W:
				ptrWindow->isPressed[Key::W] = true; break;
			case GLFW_KEY_E:
				ptrWindow->isPressed[Key::E] = true; break;
			case GLFW_KEY_R:
				ptrWindow->isPressed[Key::R] = true; break;
			case GLFW_KEY_T:
				ptrWindow->isPressed[Key::T] = true; break;
			case GLFW_KEY_Z:
				ptrWindow->isPressed[Key::Z] = true; break;
			case GLFW_KEY_U:
				ptrWindow->isPressed[Key::U] = true; break;
			case GLFW_KEY_I:
				ptrWindow->isPressed[Key::I] = true; break;
			case GLFW_KEY_O:
				ptrWindow->isPressed[Key::O] = true; break;
			case GLFW_KEY_P:
				ptrWindow->isPressed[Key::P] = true; break;
			case GLFW_KEY_A:
				ptrWindow->isPressed[Key::A] = true; break;
			case GLFW_KEY_S:
				ptrWindow->isPressed[Key::S] = true; break;
			case GLFW_KEY_D:
				ptrWindow->isPressed[Key::D] = true; break;
			case GLFW_KEY_F:
				ptrWindow->isPressed[Key::F] = true; break;
			case GLFW_KEY_G:
				ptrWindow->isPressed[Key::G] = true; break;
			case GLFW_KEY_H:
				ptrWindow->isPressed[Key::H] = true; break;
			case GLFW_KEY_J:
				ptrWindow->isPressed[Key::J] = true; break;
			case GLFW_KEY_K:
				ptrWindow->isPressed[Key::K] = true; break;
			case GLFW_KEY_L:
				ptrWindow->isPressed[Key::L] = true; break;
			case GLFW_KEY_Y:
				ptrWindow->isPressed[Key::Y] = true; break;
			case GLFW_KEY_X:
				ptrWindow->isPressed[Key::X] = true; break;
			case GLFW_KEY_C:
				ptrWindow->isPressed[Key::C] = true; break;
			case GLFW_KEY_V:
				ptrWindow->isPressed[Key::B] = true; break;
			case GLFW_KEY_N:
				ptrWindow->isPressed[Key::N] = true; break;
			case GLFW_KEY_M:
				ptrWindow->isPressed[Key::M] = true; break;
			case GLFW_KEY_1:
				ptrWindow->isPressed[Key::One] = true; break;
			case GLFW_KEY_2:
				ptrWindow->isPressed[Key::Two] = true; break;
			case GLFW_KEY_3:
				ptrWindow->isPressed[Key::Three] = true; break;
			case GLFW_KEY_4:
				ptrWindow->isPressed[Key::Four] = true; break;
			case GLFW_KEY_5:
				ptrWindow->isPressed[Key::Five] = true; break;
			case GLFW_KEY_6:
				ptrWindow->isPressed[Key::Six] = true; break;
			case GLFW_KEY_7:
				ptrWindow->isPressed[Key::Seven] = true; break;
			case GLFW_KEY_8:
				ptrWindow->isPressed[Key::Eight] = true; break;
			case GLFW_KEY_9:
				ptrWindow->isPressed[Key::Nine] = true; break;
			case GLFW_KEY_0:
				ptrWindow->isPressed[Key::Zero] = true; break;
			case GLFW_KEY_ENTER:
				ptrWindow->isPressed[Key::Enter] = true; break;
			case GLFW_KEY_SPACE:
				ptrWindow->isPressed[Key::Space] = true; break;
			case GLFW_KEY_LEFT_SHIFT:
				ptrWindow->isPressed[Key::L_shift] = true; break;
			case GLFW_KEY_LEFT_CONTROL:
				ptrWindow->isPressed[Key::L_ctrl] = true; break;
			case GLFW_KEY_LEFT_ALT:
				ptrWindow->isPressed[Key::L_alt] = true; break;
			case GLFW_KEY_RIGHT_ALT:
				ptrWindow->isPressed[Key::R_alt] = true; break;
			case GLFW_KEY_RIGHT_SHIFT:
				ptrWindow->isPressed[Key::R_shift] = true; break;
			case GLFW_KEY_RIGHT_CONTROL:
				ptrWindow->isPressed[Key::R_ctrl] = true; break;
			case GLFW_KEY_BACKSPACE:
				ptrWindow->isPressed[Key::Backspace] = true; break;
			default:
				std::cout << "Unknown key.\n";			
				break;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				ptrWindow->isPressed[Key::Escape] = false; break;
			case GLFW_KEY_Q:
				ptrWindow->isPressed[Key::Q] = false; break;
			case GLFW_KEY_W:
				ptrWindow->isPressed[Key::W] = false; break;
			case GLFW_KEY_E:
				ptrWindow->isPressed[Key::E] = false; break;
			case GLFW_KEY_R:
				ptrWindow->isPressed[Key::R] = false; break;
			case GLFW_KEY_T:
				ptrWindow->isPressed[Key::T] = false; break;
			case GLFW_KEY_Z:
				ptrWindow->isPressed[Key::Z] = false; break;
			case GLFW_KEY_U:
				ptrWindow->isPressed[Key::U] = false; break;
			case GLFW_KEY_I:
				ptrWindow->isPressed[Key::I] = false; break;
			case GLFW_KEY_O:
				ptrWindow->isPressed[Key::O] = false; break;
			case GLFW_KEY_P:
				ptrWindow->isPressed[Key::P] = false; break;
			case GLFW_KEY_A:
				ptrWindow->isPressed[Key::A] = false; break;
			case GLFW_KEY_S:
				ptrWindow->isPressed[Key::S] = false; break;
			case GLFW_KEY_D:
				ptrWindow->isPressed[Key::D] = false; break;
			case GLFW_KEY_F:
				ptrWindow->isPressed[Key::F] = false; break;
			case GLFW_KEY_G:
				ptrWindow->isPressed[Key::G] = false; break;
			case GLFW_KEY_H:
				ptrWindow->isPressed[Key::H] = false; break;
			case GLFW_KEY_J:
				ptrWindow->isPressed[Key::J] = false; break;
			case GLFW_KEY_K:
				ptrWindow->isPressed[Key::K] = false; break;
			case GLFW_KEY_L:
				ptrWindow->isPressed[Key::L] = false; break;
			case GLFW_KEY_Y:
				ptrWindow->isPressed[Key::Y] = false; break;
			case GLFW_KEY_X:
				ptrWindow->isPressed[Key::X] = false; break;
			case GLFW_KEY_C:
				ptrWindow->isPressed[Key::C] = false; break;
			case GLFW_KEY_V:
				ptrWindow->isPressed[Key::B] = false; break;
			case GLFW_KEY_N:
				ptrWindow->isPressed[Key::N] = false; break;
			case GLFW_KEY_M:
				ptrWindow->isPressed[Key::M] = false; break;
			case GLFW_KEY_1:
				ptrWindow->isPressed[Key::One] = false; break;
			case GLFW_KEY_2:
				ptrWindow->isPressed[Key::Two] = false; break;
			case GLFW_KEY_3:
				ptrWindow->isPressed[Key::Three] = false; break;
			case GLFW_KEY_4:
				ptrWindow->isPressed[Key::Four] = false; break;
			case GLFW_KEY_5:
				ptrWindow->isPressed[Key::Five] = false; break;
			case GLFW_KEY_6:
				ptrWindow->isPressed[Key::Six] = false; break;
			case GLFW_KEY_7:
				ptrWindow->isPressed[Key::Seven] = false; break;
			case GLFW_KEY_8:
				ptrWindow->isPressed[Key::Eight] = false; break;
			case GLFW_KEY_9:
				ptrWindow->isPressed[Key::Nine] = false; break;
			case GLFW_KEY_0:
				ptrWindow->isPressed[Key::Zero] = false; break;
			case GLFW_KEY_ENTER:
				ptrWindow->isPressed[Key::Enter] = false; break;
			case GLFW_KEY_SPACE:
				ptrWindow->isPressed[Key::Space] = false; break;
			case GLFW_KEY_LEFT_SHIFT:
				ptrWindow->isPressed[Key::L_shift] = false; break;
			case GLFW_KEY_LEFT_CONTROL:
				ptrWindow->isPressed[Key::L_ctrl] = false; break;
			case GLFW_KEY_LEFT_ALT:
				ptrWindow->isPressed[Key::L_alt] = false; break;
			case GLFW_KEY_RIGHT_ALT:
				ptrWindow->isPressed[Key::R_alt] = false; break;
			case GLFW_KEY_RIGHT_SHIFT:
				ptrWindow->isPressed[Key::R_shift] = false; break;
			case GLFW_KEY_RIGHT_CONTROL:
				ptrWindow->isPressed[Key::R_ctrl] = false; break;
			case GLFW_KEY_BACKSPACE:
				ptrWindow->isPressed[Key::Backspace] = false; break;
			default:
				break;
			}
		}
	}

	void Window::glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
	{
		Window *ptrWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

		float old_x_pos = ptrWindow->m_width / 2.0f;
		float old_y_pos = ptrWindow->m_height / 2.0f;

		ptrWindow->cursor_dxpos = xpos - old_x_pos;
		ptrWindow->cursor_dypos = ypos - old_y_pos;

#ifndef FREE_CURSOR
		glfwSetCursorPos(
			ptrWindow->m_WindowID,
			ptrWindow->m_width / 2.0f,
			ptrWindow->m_height / 2.0f);
#endif
	}
}