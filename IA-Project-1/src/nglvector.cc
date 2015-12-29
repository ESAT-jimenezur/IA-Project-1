// 20021110

#include "nglVector.h"


// Vector2D

Vector2D Vector2D::operator +(const Vector2D v)
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator -(const Vector2D v)
{
	return Vector2D(x - v.x, y - v.y);
}

float Vector2D::operator *(const Vector2D v)
{
	return x * v.x + y * v.y;
}

Vector2D Vector2D::operator *(const float f)
{
	return Vector2D(x * f, y * f);
}

float Vector2D::operator [](int i)
{
	return ((float *)&x)[i];
}

float Vector2D::length(void)
{
	return sqrtf(x * x + y * y);
}

float Vector2D::norm(void)
{
	return x * x + y * y;
}


float Vector2D::normalize(void)
{
	float l = length();

	if(l != 0.0f)
	{
		float inv = 1 / l;
		x*= l;
		y*= l;
	}

	return l;
}

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

// Vector3D

Vector3D Vector3D::operator +(const Vector3D v)
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator -(const Vector3D v)
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

float Vector3D::operator *(const Vector3D v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::operator *(const float f)
{
	return Vector3D(x * f, y * f, z * f);
}

Vector3D operator*(float s, const Vector3D v)
{
	return Vector3D(s * v.x, s * v.y, s * v.z);
}


Vector3D Vector3D::operator ^(const Vector3D v)
{
	return Vector3D(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

float Vector3D::operator [](int i)
{
	return ((float *)&x)[i];
}

float Vector3D::length(void)
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector3D::norm(void)
{
	return x * x + y * y + z * z;
}

float Vector3D::normalize(void)
{
	float l = length();

	if(l != 0.0f)
	{
		float inv = 1 / l;
		x*= inv;
		y*= inv;
		z*= inv;
	}

	return l;
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}