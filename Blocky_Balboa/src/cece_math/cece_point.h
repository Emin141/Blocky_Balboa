#pragma once

namespace cece {
	class Point
	{
	public:
		Point() : x(0), y(0), z(0) {}
		Point(float _x, float _y, float _z) 
			: x(_x), y(_y), z(_z) {}
	public:
		float x, y, z;
	};
}