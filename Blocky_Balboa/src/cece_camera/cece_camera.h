#pragma once

#include "../cece_math/cece_vector3.h"
#include "../cece_math/cece_e_angle.h"
#include "../cece_math/cece_matrix4.h"

namespace cece {

	class Camera
	{
	public:
		Camera();
	public:
		Vector3 position;
		float yaw, pitch;

		/*void moveForward();
		void moveBackward();
		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();

		void yawRight();
		void yawLeft();
		void pitchUp();
		void pitchDown();*/

		Matrix4 getMVP();

		//Vector3 forward, up, right;

	private:
		Matrix4 ViewMatrix();
		Matrix4 ProjectionMatrix();
	private:
		Matrix4 proj;
	};

}