#pragma once

#include "cece_vector3.h"

namespace cece {

	class EAngle
	{
	public:
		EAngle()
		{
			p = y = r = 0;
		}

		EAngle(float pitch, float yaw, float roll)
		{
			p = pitch;
			y = yaw;
			r = roll;
		}

	public:
		Vector3 ToVector() const;

		void Normalize();

	public:
		float p;
		float y;
		float r;
	};

}
