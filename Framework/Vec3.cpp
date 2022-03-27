#include "Vec3.h"

Vec3::Vec3()
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1A
	//HERE YOU WILL SET ALL VECTOR COMPONENTS TO 0
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

}

Vec3::Vec3(float x_, float y_, float z_)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1A
	//HERE YOU WILL SET ALL VECTOR COMPONENTS TO THE PARAMETERS SUPPLIED
	x = x_;
	y = y_;
	z = z_;
}

void Vec3::Add(Vec3 b)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1B
	//HERE YOU WILL ADD THE COMPONENTS FOR THE TWO VECTORS
	x = b.x + x;
	y = b.y + y;
	z = b.z + z;
}

void Vec3::Subtract(Vec3 b)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1B
	//HERE YOU WILL SUBTRACT THE COMPONENTS FOR THE TWO VECTORS
	x = x - b.x;
	y = y - b.y;
	z = z - b.z;

}

void Vec3::ScalarMultiplication(float s)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1C
	//HERE YOU WILL MULTIPLY THE SCALAR WITH THE VECTOR COMPONENTS
	x = x * s;
	y = y * s;
	z = z * s;

}

float Vec3::Mag()
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1D
	//HERE YOU WILL CALCULATE THE MAGNITUDE OF THE VECTOR
	//USE THE FUNCTION sqrt() TO CALCULATE THE SQUARE ROOT
	//USE THE FUNCTION pow(n, exp) TO CALCULATE THE EXPONENT OF A NUMBER

	float mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	return mag;
}

//ASSIGNMENT 2

void Vec3::Normalize()
{
	float mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	x = (x / (mag));
	y = (y / (mag));
	z = (z / (mag));
}

float Vec3::Dot(Vec3 b)
{
	return ((x * b.x) + (y * b.y) + (z * b.z));
}

Vec3 Vec3::Cross(Vec3 b)
{
	x = y * b.z - z * b.y;
	y = z * b.x - x * b.z;
	z = x * b.y - y * b.x;
	return Vec3(x, y, z);
}

void Vec3::Lerp(Vec3 b, float t)
{
	x = (1 - t) * x + (t * b.x);
	y = (1 - t) * y + (t * b.y);
	z = (1 - t) * z + (t * b.z);
}

void Vec3::RotateZ(float angle)
{
	int clonex = x;
	int cloney = y;

	x = (clonex * cos(angle)) - (cloney * sin(angle));
	y = (clonex * sin(angle)) + (cloney * cos(angle));
}

Vec3 Vec3::operator+(const Vec3& v) const
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}