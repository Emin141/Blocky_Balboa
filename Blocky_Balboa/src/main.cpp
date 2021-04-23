#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window/window_manager.h"
#include "cece_clock.h"
#include "cece_math.h"
#include "render_models/terrain.h"
#include "render_models/blocky.h"
#include "render_models/player.h"
#include "render_models/entity.h"

float g_deltaTime;

//The MVP matrix from the camera attached to the player entity
//should probably be a global variable, or external to the player instance.
//That way, draw calls in other objects could be made using the same variable
//without calling the getter and uniform for each in the loop

int main() {
	ShowConsole();
	Window window;

	Player player;

	Entity icososphere(
		"C:/users/emin1/Documents/3D models/donut.obj",
		"C:/users/emin1/Documents/3D models/basic.vert",
		"C:/users/emin1/Documents/3D models/basic.frag"
	);
	icososphere.setMVP(player.getMVP());
	icososphere.setWorldPosition({ 0.0f, 1.0f, -10.f });

	Blocky blocky_1;
	blocky_1.accessProgram()->setUniform("mvp", player.getMVP().c_arr());
	blocky_1.setWorldPosition({ 3.0f, 0.0f, -10.0f });

	Terrain terrain;
	terrain.accessProgram()->setUniform("mvp", player.getMVP().c_arr());

	while (window.isOpen()) {

		if (window.isPressed[(uint32_t)Event::Key::Escape]) window.close();
		
		window.prepareDraw();

		//Event handling should be done as an array of 
		//boolean states that define wether the key is pressed or not
		//The array should be implemented inside the window class
		//unsure wether a switch statement is a good idea - switch 
		//allows for only one state to be active at a time

		player.yaw(window.getCursorChangeX());
		player.pitch(window.getCursorChangeY());

		if (window.isPressed[(uint32_t)Event::Key::W]) player.moveForward();
		if (window.isPressed[(uint32_t)Event::Key::S]) player.moveBackward();
		if (window.isPressed[(uint32_t)Event::Key::D]) player.moveRight();
		if (window.isPressed[(uint32_t)Event::Key::A]) player.moveLeft();
		if (window.isPressed[(uint32_t)Event::Key::Space]) player.moveUp();
		if (window.isPressed[(uint32_t)Event::Key::L_shift]) player.moveDown();

		terrain.accessProgram()->updateUniform("mvp", player.getMVP().c_arr());
		terrain.draw();

		icososphere.updateMVP(player.getMVP());
		icososphere.draw();

		blocky_1.accessProgram()->updateUniform("mvp", player.getMVP().c_arr());
		blocky_1.draw();

		player.draw();

		window.swapBuffers();	
	}
	return 0;
}