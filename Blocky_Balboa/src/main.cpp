#include "window_manager/window_class.h"
#include "render_models/terrain.h"
#include "render_models/player.h"
#include "render_models/entity.h"
#include "render_models/blocky.h"

float g_delta_time;
cece::Matrix4 g_MVP;

//The MVP matrix from the camera attached to the player entity
//should probably be a global variable, or external to the player instance.
//That way, draw calls in other objects could be made using the same variable
//without calling the getter and uniform for each in the loop

int main() {
	cece::ShowConsole();
	cece::Window window(1600/2, 900/2, "Blocky", false);
	window.setFaceCullingCCW();
	
	Player player;
	g_MVP = player.getMVP();

	Entity donut1(
		"C:/users/emin1/Documents/3D models/donut.obj",
		"C:/users/emin1/Documents/3D models/basic.vert",
		"C:/users/emin1/Documents/3D models/basic.frag"
	);
	donut1.setWorldPosition({ 0.0f, 1.0f, -10.f });

	Entity donut2(
		"C:/users/emin1/Documents/3D models/donut.obj",
		"C:/users/emin1/Documents/3D models/basic.vert",
		"C:/users/emin1/Documents/3D models/basic.frag"
	);
	donut2.setWorldPosition({ 15.0f, 1.0f, -10.f });

	Blocky blocky1;
	blocky1.setWorldPosition({ 0.0f, 1.0f, -3.0f });
	blocky1.accessProgram()->setUniform("mvp", g_MVP.c_arr());

	Entity terrain(
		"./res/models/flatland.obj",
		"./res/shaders/flatland.vert",
		"./res/shaders/flatland.frag"
	);
	terrain.setWorldPosition({ 0.0f, -.4f, 0.0f });

	while (window.isOpen()) {

		using Key = Event::Key;
		if (window.keyIsPressed(Key::Escape)) window.close();

		window.prepareDraw();

		//Event handling should be done as an array of 
		//boolean states that define wether the key is pressed or not
		//The array should be implemented inside the window class
		//unsure wether a switch statement is a good idea - switch 
		//allows for only one state to be active at a time

		player.yaw(window.getCursorChangeX());
		player.pitch(window.getCursorChangeY());

		if (window.keyIsPressed(Key::W)) player.moveForward();
		if (window.keyIsPressed(Key::S)) player.moveBackward();
		if (window.keyIsPressed(Key::D)) player.moveRight();
		if (window.keyIsPressed(Key::A)) player.moveLeft();
		if (window.keyIsPressed(Key::Space)) player.moveUp();
		if (window.keyIsPressed(Key::L_shift)) player.moveDown();

		g_MVP = player.getMVP();

		blocky1.accessProgram()->updateUniform("mvp", g_MVP.c_arr());
		blocky1.draw();

		terrain.draw();
		donut1.draw();
		donut2.draw();
		player.draw();

		window.swapBuffers();
	}
	window.~Window();
	return 0;
}