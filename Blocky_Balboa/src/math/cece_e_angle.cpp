#include <cstdlib>

#include "cece_e_angle.h"

using namespace cece;

Vector3 EAngle::ToVector() const
{
	Vector3 result;

	result.x = cosf(y) * cosf(p);
	result.y = sinf(p);
	result.z = sinf(y) * cosf(p);

	return result;
}

void EAngle::Normalize()
{
	if (p > 89) p = 89;
	if (p < -89) p = -89;

	while (y < -180) y += 360;
	while (y > 180) y -= 360;
}