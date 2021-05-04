#include "player.h"

static const float PI = 4.0f * atanf(1);
static const float _2PI = 2.0f * PI;
static const float PI_half = PI / 2.0f;

static float toRadians(float degrees_angle)
{
	return PI / 180.0f * degrees_angle;
}

Player::Player()
{
	m_entity = new Entity(
		"./res/models/haze_sljabadar.vmf",
		"./res/shaders/player_shader.vert",
		"./res/shaders/player_shader.frag"
	);

	m_position = { 0.0f, 0.0f, 0.0f };

	m_camera = new cece::Camera;

	m_euler_angle = { toRadians(-15.0f), toRadians(-90.0f), 0.0f };

	m_camera_offeset = 15.0f * m_euler_angle.ToVector();
	m_camera->position = m_position - m_camera_offeset;
	m_camera->pitch = PI_half / 6.0f;

	m_forward = { 0.0f, 0.0f, -1.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_right = { 1.0f, 0.0f, 0.0f };

	model_matrix = cece::createTranslationMatrix(-1.0f * m_position);

	m_entity->accessProgram()->set_uniform(UniformType::MAT4, "mvp", m_camera->getMVP().c_arr());
	m_entity->accessProgram()->set_uniform(UniformType::MAT4, "model_matrix", model_matrix.c_arr());

	lin_speed = 20.0f;
	rot_speed = 4.0f;
	mouse_sensitivity = PI_half/6.0f;
}

Player::~Player()
{
	delete m_camera;
	delete m_entity;
}

void Player::updateCameraPosition()
{
	m_camera_offeset = 15.0f * m_euler_angle.ToVector();
	m_camera->position = m_position - m_camera_offeset;
}

void Player::updateToShader()
{
	model_matrix = cece::createTranslationMatrix(m_position)
		* cece::createYRotationMatrix(-1.0f * m_camera->yaw);
	m_entity->accessProgram()->update_uniform(UniformType::MAT4, "model_matrix", model_matrix.c_arr());
	m_entity->accessProgram()->update_uniform(UniformType::MAT4, "mvp", m_camera->getMVP().c_arr());
}

void Player::moveForward()
{
	m_position += m_forward * g_delta_time * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void Player::moveBackward()
{
	m_position -= m_forward * g_delta_time * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void Player::moveRight()
{
	m_position += m_right * g_delta_time * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void Player::moveLeft()
{
	m_position -= m_right * g_delta_time * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void Player::moveUp()
{
	m_position += m_up * g_delta_time * lin_speed;

	updateCameraPosition();
	updateToShader();
}

void Player::moveDown()
{
	m_position -= m_up * g_delta_time * lin_speed;
	if (m_position.y < 0.001) m_position.y = 0.0f;

	updateCameraPosition();
	updateToShader();
}

void Player::yawRight()
{
	m_euler_angle.y += g_delta_time * rot_speed;
	m_euler_angle.y = fmodf(m_euler_angle.y, _2PI);
	m_forward = m_euler_angle.ToVector();
	m_forward.y = 0;
	m_forward.normalize();
	m_right = m_forward.CrossMultiply(m_up);

	m_camera->yaw = m_euler_angle.y + PI_half;
	updateCameraPosition();
	updateToShader();
}

void Player::yawLeft()
{
	m_euler_angle.y -= g_delta_time * rot_speed;
	m_euler_angle.y = fmodf(m_euler_angle.y, _2PI);
	m_forward = m_euler_angle.ToVector();
	m_forward.y = 0;
	m_forward.normalize();
	m_right = m_forward.CrossMultiply(m_up);

	m_camera->yaw = m_euler_angle.y + PI_half;
	updateCameraPosition();
	updateToShader();
}

void Player::yaw(float dx)
{
	m_euler_angle.y += g_delta_time * dx * mouse_sensitivity;
	m_euler_angle.y = fmodf(m_euler_angle.y, _2PI);
	m_forward = m_euler_angle.ToVector();
	m_forward.y = 0;
	m_forward.normalize();
	m_right = m_forward.CrossMultiply(m_up);

	m_camera->yaw = m_euler_angle.y + PI_half;
	updateCameraPosition();
	updateToShader();
}

void Player::pitch(float dy)
{
	m_euler_angle.p -= g_delta_time * dy * mouse_sensitivity;
	if (m_euler_angle.p < - (PI_half-0.025f)) m_euler_angle.p = -(PI_half-0.025f);
	if (m_euler_angle.p > 0.0f) m_euler_angle.p = 0.0f;
	
	m_forward = m_euler_angle.ToVector();
	m_forward.y = 0;
	m_forward.normalize();
	m_right = m_forward.CrossMultiply(m_up);

	m_camera->pitch = -1.0f * m_euler_angle.p;
	updateCameraPosition();
	updateToShader();
}

void Player::draw() const
{
	m_entity->draw();
}