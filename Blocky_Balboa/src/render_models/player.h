#pragma once

#include <cstdlib>

#include "blocky.h"
#include "../camera/cece_camera.h"
#include "../math/cece_vector3.h"
#include "../math/cece_matrix4.h"
#include "../math/cece_e_angle.h"

extern float g_deltaTime;

class Player : public Blocky
{
public:
	Player();
	~Player();
	inline cece::Matrix4 getMVP() const { return m_camera->getMVP(); }

	void moveForward();
	void moveBackward();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void yawRight();
	void yawLeft();

	void yaw(float dx);
	void pitch(float dy);

private:
	cece::Vector3 m_position;
	cece::Vector3 m_forward, m_up, m_right;
	cece::Camera* m_camera;
	cece::EAngle m_euler_angle;
	cece::Vector3 m_camera_offeset;
	cece::Matrix4 model_matrix;

	float lin_speed, rot_speed, mouse_sensitivity;

	void updateCameraPosition();
	void updateToShader();
};

