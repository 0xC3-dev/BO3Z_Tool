#pragma once
#include <limits>
#include <algorithm>
#include <cmath>

class vec4_t
{
public:
	vec4_t();
	vec4_t(float, float, float, float);
	~vec4_t();

	float x, y, z, w;

	vec4_t& operator+=(const vec4_t& v) {
		x += v.x; y += v.y; z += v.z; w += v.w; return *this;
	}
	vec4_t& operator-=(const vec4_t& v) {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;
	}
	vec4_t& operator*=(float v) {
		x *= v; y *= v; z *= v; w *= v; return *this;
	}
	bool operator==(const vec4_t& v) {
		return (x == v.x) && (y == v.y);
	}
	vec4_t operator+(const vec4_t& v) {
		return vec4_t{ x + v.x, y + v.y, z + v.z, w + v.w };
	}
	vec4_t operator-(const vec4_t& v) {
		return vec4_t{ x - v.x, y - v.y, z - v.z, w - v.w };
	}
	vec4_t operator*(float fl) const {
		return vec4_t(x * fl, y * fl, z * fl, w * fl);
	}
	vec4_t operator*(const vec4_t& v) const {
		return vec4_t(x * v.x, y * v.y, z * v.z, w * v.w);
	}
	vec4_t& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;
		w /= fl;
		return *this;
	}
	auto operator-(const vec4_t& other) const -> vec4_t {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;
		buf.w -= other.w;

		return buf;
	}

	auto operator/(float other) const {
		vec4_t vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		vec.w = w / other;
		return vec;
	}

	void init(float ix, float iy, float iz, float iw);
};

class vec3_t {
public:
	vec3_t();
	vec3_t(float, float, float);
	~vec3_t();

	float x, y, z;

	vec3_t& operator+=(const vec3_t& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	vec3_t& operator-=(const vec3_t& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	vec3_t& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}
	bool operator==(const vec3_t& v) {
		return (x == v.x) && (y == v.y);
	}
	vec3_t operator+(const vec3_t& v) {
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}
	vec3_t operator-(const vec3_t& v) {
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}
	vec3_t operator*(float fl) const {
		return vec3_t(x * fl, y * fl, z * fl);
	}
	vec3_t operator*(const vec3_t& v) const {
		return vec3_t(x * v.x, y * v.y, z * v.z);
	}
	vec3_t& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}
	auto operator-(const vec3_t& other) const -> vec3_t {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	auto operator/(float other) const {
		vec3_t vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		return vec;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}
	float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline float Length2D() const
	{
		return sqrt((x * x) + (y * y));
	}
	void crossproduct(vec3_t v1, vec3_t v2, vec3_t cross_p) const //ijk = xyz
	{
		cross_p.x = (v1.y * v2.z) - (v1.z * v2.y); //i
		cross_p.y = -((v1.x * v2.z) - (v1.z * v2.x)); //j
		cross_p.z = (v1.x * v2.y) - (v1.y * v2.x); //k
	}
	vec3_t Cross(const vec3_t& vOther) const
	{
		vec3_t res;
		crossproduct(*this, vOther, res);
		return res;
	}
	bool IsZero() const
	{
		return this->x + this->y + this->z == 0;
	}

	void init(float ix, float iy, float iz);
	vec3_t clamp();
	vec3_t clamped();
	vec3_t normalized();
	float normalize_float();
	float distance_to(const vec3_t& other);
	void normalize();
	float length();
	float length_2d_sqr(void) const;
	float Dot(const vec3_t& other);
	float dot(const vec3_t other);
	float dot(const float* other);
};

class vec2_t {
public:
	float x, y;

	vec2_t() {
		x = 0; y = 0;
	};
	vec2_t(float X, float Y) {
		x = X; y = Y;
	};
	vec2_t(vec3_t vec) {
		x = vec.x; y = vec.y;
	}

	inline vec2_t operator*(const float n) const {
		return vec2_t(x * n, y * n);
	}
	inline vec2_t operator+(const vec2_t& v) const {
		return vec2_t(x + v.x, y + v.y);
	}
	inline vec2_t operator-(const vec2_t& v) const {
		return vec2_t(x - v.x, y - v.y);
	}
	inline void operator+=(const vec2_t& v) {
		x += v.x;
		y += v.y;
	}
	inline void operator-=(const vec2_t& v) {
		x -= v.x;
		y -= v.y;
	}

	bool operator>(const vec2_t& v) const {
		return (v.x > x && v.y > y);
	}
	bool operator==(const vec2_t& v) const {
		return (v.x == x && v.y == y);
	}
	bool operator!=(const vec2_t& v) const {
		return (v.x != x || v.y != y);
	}

	inline float length() {
		return sqrt((x * x) + (y * y));
	}
};