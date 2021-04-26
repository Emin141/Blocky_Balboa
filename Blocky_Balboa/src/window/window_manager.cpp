#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include "window_manager.h"
#include "../shader_manager/logger.h"

extern float g_deltaTime;

Window::Window()
{
	init();
	setCallbaks();
}

void Window::updateFPSCounter() {
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf(tmp, "Blocky Balboa @ fps: %.2f", fps);
		glfwSetWindowTitle(m_WindowID, tmp);
		frame_count = 0;
	}
	frame_count++;
}

void Window::setFaceCullingCW(bool set)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_WindowID);
	glfwPollEvents();
}

void Window::clear(Color color) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (color)
	{
	case Color::NONE:
		glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
		break;
	case Color::WHITE:
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case Color::BLACK:
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case Color::RED:
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case Color::GREEN:
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case Color::BLUE:
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case Color::YELLOW:
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case Color::CYAN:
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	case Color::MAGENTA:
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}

void Window::prepareDraw()
{
	g_deltaTime = m_clock.deltaTime();

	updateFPSCounter();
	setSize();
	clear();
}

void ShowConsole(bool show)
{
	ShowWindow(GetConsoleWindow(), show ? SW_SHOW : SW_HIDE);
}

void Window::init()
{
	assert(restart_gl_log());

	// start GL context and O/S window using the GLFW helper library
	gl_log("Starting GLFW\n%s\n", glfwGetVersionString());

	glfwSetWindowUserPointer(m_WindowID, this); //wtf?

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	/*if (fullscreen_enabled) {
		GLFWmonitor* mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(mon);
		m_WindowID = glfwCreateWindow(vmode->width, vmode->height, "Extended GLInit", mon, NULL);
	}
	else { m_WindowID = glfwCreateWindow(g_width, g_height, "Extended GLInit", NULL, NULL); }*/

	m_width = 1600;
	m_height = 900;

	m_WindowID = glfwCreateWindow(m_width, m_height, "Window", NULL, NULL);

	if (!m_WindowID)
	{
		fprintf(stderr, "ERROR: could not create window with GLFW3\n");
		exit(-1);
	}
	glfwMakeContextCurrent(m_WindowID);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	gl_log("Renderer: %s\n", renderer);
	gl_log("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(m_WindowID, this);

	for (auto i : isPressed) { i = false; }

	glfwSetInputMode(m_WindowID, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(m_WindowID, m_width / 2.0f, m_height / 2.0f);
}