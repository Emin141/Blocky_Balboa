#include <cstdio>

#include "window_manager.h"
#include "../shader_manager/logger.h"

void Window::setCallbaks()
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwSetWindowSizeCallback(m_WindowID, glfw_window_size_callback);
	glfwSetKeyCallback(m_WindowID, glfw_key_callback);
	glfwSetCursorPosCallback(m_WindowID, glfw_cursor_position_callback);
}

void Window::glfw_error_callback(int error, const char* description) {
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

void Window::glfw_window_size_callback(GLFWwindow* window, int width, int height)
{
	Window* ptrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	ptrWindow->m_width = width;
	ptrWindow->m_height = height;
	ptrWindow->setSize();
}

void Window::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* ptrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	using Key = Event::Key;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			ptrWindow->isPressed[(uint32_t)Key::Escape] = true;
			break;
		case GLFW_KEY_Q:
			ptrWindow->isPressed[(uint32_t)Key::Q] = true;
			break;
		case GLFW_KEY_W:
			ptrWindow->isPressed[(uint32_t)Key::W] = true;
			break;
		case GLFW_KEY_E:
			ptrWindow->isPressed[(uint32_t)Key::E] = true;
			break;
		case GLFW_KEY_R:
			ptrWindow->isPressed[(uint32_t)Key::R] = true;
			break;
		case GLFW_KEY_T:
			ptrWindow->isPressed[(uint32_t)Key::T] = true;
			break;
		case GLFW_KEY_Z:
			ptrWindow->isPressed[(uint32_t)Key::Z] = true;
			break;
		case GLFW_KEY_U:
			ptrWindow->isPressed[(uint32_t)Key::U] = true;
			break;
		case GLFW_KEY_I:
			ptrWindow->isPressed[(uint32_t)Key::I] = true;
			break;
		case GLFW_KEY_O:
			ptrWindow->isPressed[(uint32_t)Key::O] = true;
			break;
		case GLFW_KEY_P:
			ptrWindow->isPressed[(uint32_t)Key::P] = true;
			break;
		case GLFW_KEY_A:
			ptrWindow->isPressed[(uint32_t)Key::A] = true;
			break;
		case GLFW_KEY_S:
			ptrWindow->isPressed[(uint32_t)Key::S] = true;
			break;
		case GLFW_KEY_D:
			ptrWindow->isPressed[(uint32_t)Key::D] = true;
			break;
		case GLFW_KEY_F:
			ptrWindow->isPressed[(uint32_t)Key::F] = true;
			break;
		case GLFW_KEY_G:
			ptrWindow->isPressed[(uint32_t)Key::G] = true;
			break;
		case GLFW_KEY_H:
			ptrWindow->isPressed[(uint32_t)Key::H] = true;
			break;
		case GLFW_KEY_J:
			ptrWindow->isPressed[(uint32_t)Key::J] = true;
			break;
		case GLFW_KEY_K:
			ptrWindow->isPressed[(uint32_t)Key::K] = true;
			break;
		case GLFW_KEY_L:
			ptrWindow->isPressed[(uint32_t)Key::L] = true;
			break;
		case GLFW_KEY_Y:
			ptrWindow->isPressed[(uint32_t)Key::Y] = true;
			break;
		case GLFW_KEY_X:
			ptrWindow->isPressed[(uint32_t)Key::X] = true;
			break;
		case GLFW_KEY_C:
			ptrWindow->isPressed[(uint32_t)Key::C] = true;
			break;
		case GLFW_KEY_V:
			ptrWindow->isPressed[(uint32_t)Key::B] = true;
			break;
		case GLFW_KEY_N:
			ptrWindow->isPressed[(uint32_t)Key::N] = true;
			break;
		case GLFW_KEY_M:
			ptrWindow->isPressed[(uint32_t)Key::M] = true;
			break;
		case GLFW_KEY_1:
			ptrWindow->isPressed[(uint32_t)Key::One] = true;
			break;
		case GLFW_KEY_2:
			ptrWindow->isPressed[(uint32_t)Key::Two] = true;
			break;
		case GLFW_KEY_3:
			ptrWindow->isPressed[(uint32_t)Key::Three] = true;
			break;
		case GLFW_KEY_4:
			ptrWindow->isPressed[(uint32_t)Key::Four] = true;
			break;
		case GLFW_KEY_5:
			ptrWindow->isPressed[(uint32_t)Key::Five] = true;
			break;
		case GLFW_KEY_6:
			ptrWindow->isPressed[(uint32_t)Key::Six] = true;
			break;
		case GLFW_KEY_7:
			ptrWindow->isPressed[(uint32_t)Key::Seven] = true;
			break;
		case GLFW_KEY_8:
			ptrWindow->isPressed[(uint32_t)Key::Eight] = true;
			break;
		case GLFW_KEY_9:
			ptrWindow->isPressed[(uint32_t)Key::Nine] = true;
			break;
		case GLFW_KEY_0:
			ptrWindow->isPressed[(uint32_t)Key::Zero] = true;
			break;
		case GLFW_KEY_ENTER:
			ptrWindow->isPressed[(uint32_t)Key::Enter] = true;
			break;
		case GLFW_KEY_SPACE:
			ptrWindow->isPressed[(uint32_t)Key::Space] = true;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			ptrWindow->isPressed[(uint32_t)Key::L_shift] = true;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			ptrWindow->isPressed[(uint32_t)Key::L_ctrl] = true;
			break;
		case GLFW_KEY_LEFT_ALT:
			ptrWindow->isPressed[(uint32_t)Key::L_alt] = true;
			break;
		case GLFW_KEY_RIGHT_ALT:
			ptrWindow->isPressed[(uint32_t)Key::R_alt] = true;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			ptrWindow->isPressed[(uint32_t)Key::R_shift] = true;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			ptrWindow->isPressed[(uint32_t)Key::R_ctrl] = true;
			break;
		case GLFW_KEY_BACKSPACE:
			ptrWindow->isPressed[(uint32_t)Key::Backspace] = true;
			break;
		default:
			//ptrWindow->isPressed[(uint32_t)Key::None] = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			ptrWindow->isPressed[(uint32_t)Key::Escape] = false;
			break;
		case GLFW_KEY_Q:
			ptrWindow->isPressed[(uint32_t)Key::Q] = false;
			break;
		case GLFW_KEY_W:
			ptrWindow->isPressed[(uint32_t)Key::W] = false;
			break;
		case GLFW_KEY_E:
			ptrWindow->isPressed[(uint32_t)Key::E] = false;
			break;
		case GLFW_KEY_R:
			ptrWindow->isPressed[(uint32_t)Key::R] = false;
			break;
		case GLFW_KEY_T:
			ptrWindow->isPressed[(uint32_t)Key::T] = false;
			break;
		case GLFW_KEY_Z:
			ptrWindow->isPressed[(uint32_t)Key::Z] = false;
			break;
		case GLFW_KEY_U:
			ptrWindow->isPressed[(uint32_t)Key::U] = false;
			break;
		case GLFW_KEY_I:
			ptrWindow->isPressed[(uint32_t)Key::I] = false;
			break;
		case GLFW_KEY_O:
			ptrWindow->isPressed[(uint32_t)Key::O] = false;
			break;
		case GLFW_KEY_P:
			ptrWindow->isPressed[(uint32_t)Key::P] = false;
			break;
		case GLFW_KEY_A:
			ptrWindow->isPressed[(uint32_t)Key::A] = false;
			break;
		case GLFW_KEY_S:
			ptrWindow->isPressed[(uint32_t)Key::S] = false;
			break;
		case GLFW_KEY_D:
			ptrWindow->isPressed[(uint32_t)Key::D] = false;
			break;
		case GLFW_KEY_F:
			ptrWindow->isPressed[(uint32_t)Key::F] = false;
			break;
		case GLFW_KEY_G:
			ptrWindow->isPressed[(uint32_t)Key::G] = false;
			break;
		case GLFW_KEY_H:
			ptrWindow->isPressed[(uint32_t)Key::H] = false;
			break;
		case GLFW_KEY_J:
			ptrWindow->isPressed[(uint32_t)Key::J] = false;
			break;
		case GLFW_KEY_K:
			ptrWindow->isPressed[(uint32_t)Key::K] = false;
			break;
		case GLFW_KEY_L:
			ptrWindow->isPressed[(uint32_t)Key::L] = false;
			break;
		case GLFW_KEY_Y:
			ptrWindow->isPressed[(uint32_t)Key::Y] = false;
			break;
		case GLFW_KEY_X:
			ptrWindow->isPressed[(uint32_t)Key::X] = false;
			break;
		case GLFW_KEY_C:
			ptrWindow->isPressed[(uint32_t)Key::C] = false;
			break;
		case GLFW_KEY_V:
			ptrWindow->isPressed[(uint32_t)Key::B] = false;
			break;
		case GLFW_KEY_N:
			ptrWindow->isPressed[(uint32_t)Key::N] = false;
			break;
		case GLFW_KEY_M:
			ptrWindow->isPressed[(uint32_t)Key::M] = false;
			break;
		case GLFW_KEY_1:
			ptrWindow->isPressed[(uint32_t)Key::One] = false;
			break;
		case GLFW_KEY_2:
			ptrWindow->isPressed[(uint32_t)Key::Two] = false;
			break;
		case GLFW_KEY_3:
			ptrWindow->isPressed[(uint32_t)Key::Three] = false;
			break;
		case GLFW_KEY_4:
			ptrWindow->isPressed[(uint32_t)Key::Four] = false;
			break;
		case GLFW_KEY_5:
			ptrWindow->isPressed[(uint32_t)Key::Five] = false;
			break;
		case GLFW_KEY_6:
			ptrWindow->isPressed[(uint32_t)Key::Six] = false;
			break;
		case GLFW_KEY_7:
			ptrWindow->isPressed[(uint32_t)Key::Seven] = false;
			break;
		case GLFW_KEY_8:
			ptrWindow->isPressed[(uint32_t)Key::Eight] = false;
			break;
		case GLFW_KEY_9:
			ptrWindow->isPressed[(uint32_t)Key::Nine] = false;
			break;
		case GLFW_KEY_0:
			ptrWindow->isPressed[(uint32_t)Key::Zero] = false;
			break;
		case GLFW_KEY_ENTER:
			ptrWindow->isPressed[(uint32_t)Key::Enter] = false;
			break;
		case GLFW_KEY_SPACE:
			ptrWindow->isPressed[(uint32_t)Key::Space] = false;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			ptrWindow->isPressed[(uint32_t)Key::L_shift] = false;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			ptrWindow->isPressed[(uint32_t)Key::L_ctrl] = false;
			break;
		case GLFW_KEY_LEFT_ALT:
			ptrWindow->isPressed[(uint32_t)Key::L_alt] = false;
			break;
		case GLFW_KEY_RIGHT_ALT:
			ptrWindow->isPressed[(uint32_t)Key::R_alt] = false;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			ptrWindow->isPressed[(uint32_t)Key::R_shift] = false;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			ptrWindow->isPressed[(uint32_t)Key::R_ctrl] = false;
			break;
		case GLFW_KEY_BACKSPACE:
			ptrWindow->isPressed[(uint32_t)Key::Backspace] = false;
			break;
		default:
			//ptrWindow->isPressed[(uint32_t)Key::None] = false;
			break;
		}
	}
}

void Window::glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* ptrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	double old_x_pos = ptrWindow->m_width / 2.0f;
	double old_y_pos = ptrWindow->m_height / 2.0f;

	ptrWindow->cursor_dxpos = xpos - old_x_pos;
	ptrWindow->cursor_dypos = ypos - old_y_pos;

	glfwSetCursorPos(
		ptrWindow->m_WindowID,
		ptrWindow->m_width / 2.0f,
		ptrWindow->m_height / 2.0f
	);
}