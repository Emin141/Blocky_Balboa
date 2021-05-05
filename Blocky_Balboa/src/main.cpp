#include <string>
#include <iostream>
#include "window_manager/window_class.h"
#include "opengl_classes/new_mesh_class.h"
#include "opengl_classes/shader_class.h"
#include "cece_camera/cece_camera.h"
#include "opengl_classes/vao_class.h"
#include "opengl_classes/vbo_class.h"
#include "opengl_classes/ebo_class.h"

float g_delta_time;

int main()
{
	cece::show_console_window();
	cece::Window window(640, 640 * 9 / 16, "Blocky", false);

	cece::Camera camera;

	cece::Matrix4 model_matrix;
	cece::Matrix4 mvp_matrix = camera.getMVP();

	model_matrix.print();
	mvp_matrix.print();

	Shader shader_program("./res/shaders/colored_icososphere.frag",
						  "./res/shaders/colored_icososphere.frag");
	shader_program.Activate();
	shader_program.set_uniform(UniformType::MAT4, "model_matrix", model_matrix.c_arr());
	shader_program.set_uniform(UniformType::MAT4, "mvp", mvp_matrix.c_arr());

	GLfloat vertex_data[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3};

	VAO vao;
	vao.Bind();

	VBO vbo(vertex_data, sizeof(vertex_data));
	EBO ebo(indices, sizeof(indices));

	vbo.Bind();
	ebo.Bind();

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	while (window.isOpen())
	{

		using Key = Event::Key;
		if (window.keyIsPressed(Key::Escape))
			window.close();

		window.prepareDraw();

		shader_program.Activate();
		ebo.Bind();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6,
					   GL_UNSIGNED_INT, nullptr);

		shader_program.Deactivate();
		vao.Unbind();
		ebo.Unbind();

		window.pollEvents();
		window.swapBuffers();
	}
	window.~Window();
	return 0;
}