#pragma once

struct Vec4
{
	float x, y, z, w;
};

struct Vec3
{
	float x, y, z;

	float length(void) {
		auto sqr = [](float n) {
			return static_cast<float>(n * n);
		};

		return sqrt(sqr(x) + sqr(y) + sqr(z));
	}

	float GetDistance(const Vec3& other)
	{
		Vec3 delta;
		delta.x = x - other.x;
		delta.y = y - other.y;
		delta.z = z - other.z;

		return delta.length();
	}
};

struct Vec2
{
	float x, y;
};