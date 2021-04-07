#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include "window_manager.h"
#include "logger.h"

void glfw_error_callback(int error, const char* description) {
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

// keep track of window size for things like the viewport and the mouse cursor
extern int g_gl_width;
extern int g_gl_height;

// a call-back function
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;
	/* update any perspective matrices used here */
}

Window::Window(const bool fullscreen_enabled)
{
	assert(restart_gl_log());

	// start GL context and O/S window using the GLFW helper library
	gl_log("Starting GLFW\n%s\n", glfwGetVersionString());

	// register the error call-back function that we wrote, above
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	if (fullscreen_enabled) {
		GLFWmonitor* mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(mon);
		m_WindowID = glfwCreateWindow(vmode->width, vmode->height, "Extended GLInit", mon, NULL);
	}
	else { m_WindowID = glfwCreateWindow(g_gl_width, g_gl_height, "Extended GLInit", NULL, NULL); }

	if (!m_WindowID)
	{
		fprintf(stderr, "ERROR: could not create window with GLFW3\n");
		exit(-1);
	}
	glfwMakeContextCurrent(m_WindowID);
	glfwSetWindowSizeCallback(m_WindowID, glfw_window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	gl_log("Renderer: %s\n", renderer);
	gl_log("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
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
		sprintf(tmp, "opengl @ fps: %.2f", fps);
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

void ShowConsole(bool show)
{
	ShowWindow(GetConsoleWindow(), show ? SW_SHOW : SW_HIDE);
}