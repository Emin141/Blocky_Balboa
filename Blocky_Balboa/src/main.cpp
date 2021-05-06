#include "window_manager/window_class.h"
#include "opengl_classes/new_mesh_class.h"
#include "opengl_classes/shader_class.h"
#include "cece_camera/cece_camera.h"
#include "opengl_classes/texture_class.h"

float g_delta_time;

int main()
{
	cece::show_console_window();
	cece::Window window(1200, 1200 * 9 / 16, "Blocky", false);
	window.setFaceCullingCCW();

	cece::Camera camera;
	camera.position = { 0.0f, 1.0f, 4.0f };
	camera.pitch = 0.2f;

	cece::Matrix4 model_matrix;
	cece::Matrix4 mvp_matrix = camera.getMVP();

	Shader shader_program("colored_icososphere");
	shader_program.Activate();
	shader_program.set_uniform(UniformType::MAT4, "model_matrix", model_matrix.c_arr());
	shader_program.set_uniform(UniformType::MAT4, "mvp", mvp_matrix.c_arr());

	std::string texture_source;
	Mesh mesh("colored_icososphere", texture_source);

	Texture texture(texture_source.c_str(), GL_TEXTURE_2D,
					GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	
	while (window.isOpen())
	{
		using Key = Event::Key;
		if (window.keyIsPressed(Key::Escape))
			window.close();

		window.prepareDraw();

		shader_program.Activate();
		mesh.bind();
		texture.Bind();

		glDrawElements(GL_TRIANGLES, mesh.number_of_indices,
			GL_UNSIGNED_INT, NULL);

		shader_program.Deactivate();
		mesh.unbind();
		texture.Unbind();

		window.pollEvents();
		window.swapBuffers();
	}
	window.~Window();
	return 0;
}