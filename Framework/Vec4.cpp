#include "Vec4.h"

Vec4::Vec4()
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1A
	//HERE YOU WILL SET ALL VECTOR COMPONENTS TO 0
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	d = 1.0f;
}

Vec4::Vec4(float x_, float y_, float z_, float d_)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1A
	//HERE YOU WILL SET ALL VECTOR COMPONENTS TO THE PARAMETERS SUPPLIED
	x = x_;
	y = y_;
	z = z_;
	d = d_;
}

void Vec4::Add(Vec4 b)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1B
	//HERE YOU WILL ADD THE COMPONENTS FOR THE TWO VECTORS
	x = b.x + x;
	y = b.y + y;
	z = b.z + z;
	d = b.d + d;
}

void Vec4::Subtract(Vec4 b)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1B
	//HERE YOU WILL SUBTRACT THE COMPONENTS FOR THE TWO VECTORS
	x = x - b.x;
	y = y - b.y;
	z = z - b.z;
	d = d - b.d;

}

void Vec4::ScalarMultiplication(float s)
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1C
	//HERE YOU WILL MULTIPLY THE SCALAR WITH THE VECTOR COMPONENTS
	x = x * s;
	y = y * s;
	z = z * s;
	d = d * s;

}

float Vec4::Mag()
{
	//COMPLETE THIS MEMBER FUNCTION FOR ASSIGNMENT 1D
	//HERE YOU WILL CALCULATE THE MAGNITUDE OF THE VECTOR
	//USE THE FUNCTION sqrt() TO CALCULATE THE SQUARE ROOT
	//USE THE FUNCTION pow(n, exp) TO CALCULATE THE EXPONENT OF A NUMBER

	float mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(d, 2));

	return mag;
}

//ASSIGNMENT 2

void Vec4::Normalize()
{
	float mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(d, 2));

	x = (x / (mag));
	y = (y / (mag));
	z = (z / (mag));
	d = (d / (mag));
}


void Vec4::Lerp(Vec4 b, float t)
{
	x = (1 - t) * x + (t * b.x);
	y = (1 - t) * y + (t * b.y);
	z = (1 - t) * z + (t * b.z);
	d = (1 - t) * d + (t * b.d);

}

Vec4 Vec4::operator+(const Vec4& v) const
{
	return Vec4(x + v.x, y + v.y, z + v.z, d + v.d);
}

Vec4 Vec4::operator-(const Vec4& v) const
{
	return Vec4(x - v.x, y - v.y, z - v.z, d - v.d);
}