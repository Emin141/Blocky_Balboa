#include <cstdio>

#include "window_manager.h"
#include "../logger.h"

//extern int g_width;
//extern int g_height;

void Window::setCallbaks()
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwSetWindowSizeCallback(m_WindowID, glfw_window_size_callback);
	glfwSetKeyCallback(m_WindowID, glfw_key_callback);
}

void glfw_error_callback(int error, const char* description) {
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height)
{
	Window* ptrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	ptrWindow->m_width = width;
	ptrWindow->m_height = height;
	ptrWindow->setSize();
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* ptrWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	using Type = Event::Type;
	using Key = Event::Key;

	if (action == GLFW_PRESS)
	{
		printf("Pressed! ");
		ptrWindow->inputEvent.setType(Type::KEY_PRESS);
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			ptrWindow->inputEvent.setKey(Key::Escape);
			break;
		case GLFW_KEY_Q:
			ptrWindow->inputEvent.setKey(Key::Q);
			break;
		case GLFW_KEY_W:
			ptrWindow->inputEvent.setKey(Key::W);
			break;
		case GLFW_KEY_E:
			ptrWindow->inputEvent.setKey(Key::E);
			break;
		case GLFW_KEY_R:
			ptrWindow->inputEvent.setKey(Key::R);
			break;
		case GLFW_KEY_T:
			ptrWindow->inputEvent.setKey(Key::T);
			break;
		case GLFW_KEY_Z:
			ptrWindow->inputEvent.setKey(Key::Z);
			break;
		case GLFW_KEY_U:
			ptrWindow->inputEvent.setKey(Key::U);
			break;
		case GLFW_KEY_I:
			ptrWindow->inputEvent.setKey(Key::I);
			break;
		case GLFW_KEY_O:
			ptrWindow->inputEvent.setKey(Key::O);
			break;
		case GLFW_KEY_P:
			ptrWindow->inputEvent.setKey(Key::P);
			break;
		case GLFW_KEY_A:
			ptrWindow->inputEvent.setKey(Key::A);
			break;
		case GLFW_KEY_S:
			ptrWindow->inputEvent.setKey(Key::S);
			break;
		case GLFW_KEY_D:
			ptrWindow->inputEvent.setKey(Key::D);
			break;
		case GLFW_KEY_F:
			ptrWindow->inputEvent.setKey(Key::F);
			break;
		case GLFW_KEY_G:
			ptrWindow->inputEvent.setKey(Key::G);
			break;
		case GLFW_KEY_H:
			ptrWindow->inputEvent.setKey(Key::H);
			break;
		case GLFW_KEY_J:
			ptrWindow->inputEvent.setKey(Key::J);
			break;
		case GLFW_KEY_K:
			ptrWindow->inputEvent.setKey(Key::K);
			break;
		case GLFW_KEY_L:
			ptrWindow->inputEvent.setKey(Key::L);
			break;
		case GLFW_KEY_Y:
			ptrWindow->inputEvent.setKey(Key::Y);
			break;
		case GLFW_KEY_X:
			ptrWindow->inputEvent.setKey(Key::X);
			break;
		case GLFW_KEY_C:
			ptrWindow->inputEvent.setKey(Key::C);
			break;
		case GLFW_KEY_V:
			ptrWindow->inputEvent.setKey(Key::B);
			break;
		case GLFW_KEY_N:
			ptrWindow->inputEvent.setKey(Key::N);
			break;
		case GLFW_KEY_M:
			ptrWindow->inputEvent.setKey(Key::M);
			break;
		case GLFW_KEY_1:
			ptrWindow->inputEvent.setKey(Key::One);
			break;
		case GLFW_KEY_2:
			ptrWindow->inputEvent.setKey(Key::Two);
			break;
		case GLFW_KEY_3:
			ptrWindow->inputEvent.setKey(Key::Three);
			break;
		case GLFW_KEY_4:
			ptrWindow->inputEvent.setKey(Key::Four);
			break;
		case GLFW_KEY_5:
			ptrWindow->inputEvent.setKey(Key::Five);
			break;
		case GLFW_KEY_6:
			ptrWindow->inputEvent.setKey(Key::Six);
			break;
		case GLFW_KEY_7:
			ptrWindow->inputEvent.setKey(Key::Seven);
			break;
		case GLFW_KEY_8:
			ptrWindow->inputEvent.setKey(Key::Eight);
			break;
		case GLFW_KEY_9:
			ptrWindow->inputEvent.setKey(Key::Nine);
			break;
		case GLFW_KEY_0:
			ptrWindow->inputEvent.setKey(Key::Zero);
			break;
		case GLFW_KEY_ENTER:
			ptrWindow->inputEvent.setKey(Key::Enter);
			break;
		case GLFW_KEY_SPACE:
			ptrWindow->inputEvent.setKey(Key::Space);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			ptrWindow->inputEvent.setKey(Key::L_shift);
			break;
		case GLFW_KEY_LEFT_CONTROL:
			ptrWindow->inputEvent.setKey(Key::L_ctrl);
			break;
		case GLFW_KEY_LEFT_ALT:
			ptrWindow->inputEvent.setKey(Key::L_alt);
			break;
		case GLFW_KEY_RIGHT_ALT:
			ptrWindow->inputEvent.setKey(Key::R_alt);
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			ptrWindow->inputEvent.setKey(Key::R_shift);
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			ptrWindow->inputEvent.setKey(Key::R_ctrl);
			break;
		case GLFW_KEY_BACKSPACE:
			ptrWindow->inputEvent.setKey(Key::Backspace);
			break;
		default:
			ptrWindow->inputEvent.setKey(Key::None);
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		printf("Released! ");
		ptrWindow->inputEvent.setType(Type::KEY_RELEASE);
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			ptrWindow->inputEvent.setKey(Key::Escape);
			break;
		case GLFW_KEY_Q:
			ptrWindow->inputEvent.setKey(Key::Q);
			break;
		case GLFW_KEY_W:
			ptrWindow->inputEvent.setKey(Key::W);
			break;
		case GLFW_KEY_E:
			ptrWindow->inputEvent.setKey(Key::E);
			break;
		case GLFW_KEY_R:
			ptrWindow->inputEvent.setKey(Key::R);
			break;
		case GLFW_KEY_T:
			ptrWindow->inputEvent.setKey(Key::T);
			break;
		case GLFW_KEY_Z:
			ptrWindow->inputEvent.setKey(Key::Z);
			break;
		case GLFW_KEY_U:
			ptrWindow->inputEvent.setKey(Key::U);
			break;
		case GLFW_KEY_I:
			ptrWindow->inputEvent.setKey(Key::I);
			break;
		case GLFW_KEY_O:
			ptrWindow->inputEvent.setKey(Key::O);
			break;
		case GLFW_KEY_P:
			ptrWindow->inputEvent.setKey(Key::P);
			break;
		case GLFW_KEY_A:
			ptrWindow->inputEvent.setKey(Key::A);
			break;
		case GLFW_KEY_S:
			ptrWindow->inputEvent.setKey(Key::S);
			break;
		case GLFW_KEY_D:
			ptrWindow->inputEvent.setKey(Key::D);
			break;
		case GLFW_KEY_F:
			ptrWindow->inputEvent.setKey(Key::F);
			break;
		case GLFW_KEY_G:
			ptrWindow->inputEvent.setKey(Key::G);
			break;
		case GLFW_KEY_H:
			ptrWindow->inputEvent.setKey(Key::H);
			break;
		case GLFW_KEY_J:
			ptrWindow->inputEvent.setKey(Key::J);
			break;
		case GLFW_KEY_K:
			ptrWindow->inputEvent.setKey(Key::K);
			break;
		case GLFW_KEY_L:
			ptrWindow->inputEvent.setKey(Key::L);
			break;
		case GLFW_KEY_Y:
			ptrWindow->inputEvent.setKey(Key::Y);
			break;
		case GLFW_KEY_X:
			ptrWindow->inputEvent.setKey(Key::X);
			break;
		case GLFW_KEY_C:
			ptrWindow->inputEvent.setKey(Key::C);
			break;
		case GLFW_KEY_V:
			ptrWindow->inputEvent.setKey(Key::B);
			break;
		case GLFW_KEY_N:
			ptrWindow->inputEvent.setKey(Key::N);
			break;
		case GLFW_KEY_M:
			ptrWindow->inputEvent.setKey(Key::M);
			break;
		case GLFW_KEY_1:
			ptrWindow->inputEvent.setKey(Key::One);
			break;
		case GLFW_KEY_2:
			ptrWindow->inputEvent.setKey(Key::Two);
			break;
		case GLFW_KEY_3:
			ptrWindow->inputEvent.setKey(Key::Three);
			break;
		case GLFW_KEY_4:
			ptrWindow->inputEvent.setKey(Key::Four);
			break;
		case GLFW_KEY_5:
			ptrWindow->inputEvent.setKey(Key::Five);
			break;
		case GLFW_KEY_6:
			ptrWindow->inputEvent.setKey(Key::Six);
			break;
		case GLFW_KEY_7:
			ptrWindow->inputEvent.setKey(Key::Seven);
			break;
		case GLFW_KEY_8:
			ptrWindow->inputEvent.setKey(Key::Eight);
			break;
		case GLFW_KEY_9:
			ptrWindow->inputEvent.setKey(Key::Nine);
			break;
		case GLFW_KEY_0:
			ptrWindow->inputEvent.setKey(Key::Zero);
			break;
		case GLFW_KEY_ENTER:
			ptrWindow->inputEvent.setKey(Key::Enter);
			break;
		case GLFW_KEY_SPACE:
			ptrWindow->inputEvent.setKey(Key::Space);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			ptrWindow->inputEvent.setKey(Key::L_shift);
			break;
		case GLFW_KEY_LEFT_CONTROL:
			ptrWindow->inputEvent.setKey(Key::L_ctrl);
			break;
		case GLFW_KEY_LEFT_ALT:
			ptrWindow->inputEvent.setKey(Key::L_alt);
			break;
		case GLFW_KEY_RIGHT_ALT:
			ptrWindow->inputEvent.setKey(Key::R_alt);
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			ptrWindow->inputEvent.setKey(Key::R_shift);
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			ptrWindow->inputEvent.setKey(Key::R_ctrl);
			break;
		case GLFW_KEY_BACKSPACE:
			ptrWindow->inputEvent.setKey(Key::Backspace);
			break;
		default:
			ptrWindow->inputEvent.setKey(Key::None);
			break;
		}
	}
}