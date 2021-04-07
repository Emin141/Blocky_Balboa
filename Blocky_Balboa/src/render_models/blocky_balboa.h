#pragma once

#include <cstdlib>

#include "blocky.h"
#include "../camera/cece_camera.h"
#include "../math/cece_vector3.h"
#include "../math/cece_matrix4.h"
#include "../math/cece_e_angle.h"

typedef cece::Vector3 Direction;
extern float g_deltaTime;



class BlockyBalboa : public Blocky
{
public:
	BlockyBalboa();
	~BlockyBalboa();
	inline cece::Matrix4 getMVP() const { return m_camera->getMVP().c_arr(); }
	//inline cece::Camera* accessCamera() const { return m_camera; }

	void moveForward();
	void moveBackward();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void yawRight();
	void yawLeft();

private:
	cece::Vector3 m_position;
	Direction m_forward, m_up, m_right;
	cece::Camera* m_camera;
	cece::EAngle m_euler_angle;
	cece::Vector3 m_camera_offeset;
	cece::Matrix4 model_matrix;
	float lin_speed, rot_speed;

	void updateCameraPosition();
	void updateToShader();
};

