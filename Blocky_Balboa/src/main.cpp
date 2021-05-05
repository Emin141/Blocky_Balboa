#include "window_manager/window_class.h"
#include "entity_class/player.h"
#include "entity_class/entity.h"

float g_delta_time;
cece::Matrix4 g_MVP;

int main() {
	cece::show_console_window();
	cece::Window window(1600, 900, "Blocky", false);
	window.setFaceCullingCCW();

	Player player;
	g_MVP = player.getMVP();

	Entity donut1(
		"./res/models/donut.wfo",
		"./res/shaders/donut.vert",
		"./res/shaders/donut.frag"
	);
	donut1.setWorldPosition({ 0.0f, 1.0f, -10.f });

	Entity terrain(
		"./res/models/flatland.wfo",
		"./res/shaders/flatland.vert",
		"./res/shaders/flatland.frag"
	);
	terrain.setWorldPosition({ 0.0f, -1.0f, 0.0f });

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

		terrain.draw();
		
		donut1.updateWorldPosition({ 0.0f, 1.0f, -10.0f });
		donut1.draw();
		donut1.updateWorldPosition({ 0.0f, 1.0f, -15.0f });
		donut1.draw();
		donut1.updateWorldPosition({ 0.0f, 1.0f, -5.0f });
		donut1.draw();
		donut1.updateWorldPosition({ 5.0f, 1.0f, -10.0f });
		donut1.draw();
		donut1.updateWorldPosition({ 5.0f, 1.0f, -15.0f });
		donut1.draw();
		donut1.updateWorldPosition({ 5.0f, 1.0f, -5.0f });
		donut1.draw();
		donut1.updateWorldPosition({ -5.0f, 1.0f, -10.0f });
		donut1.draw();
		donut1.updateWorldPosition({ -5.0f, 1.0f, -15.0f });
		donut1.draw();
		donut1.updateWorldPosition({ -5.0f, 1.0f, -5.0f });
		donut1.draw();

		donut1.updateWorldPosition({-0.0f, 0.0f, 0.0f});
		donut1.draw();

		player.draw();

		window.pollEvents();
		window.swapBuffers();
	}
	window.~Window();

	return 0;
}