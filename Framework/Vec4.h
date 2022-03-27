#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include <math.h>

using namespace std;

class Vec4
{
public:
	//Class variables
	float x;
	float y;
	float z;
	float d;
	//Construct
	Vec4();
	Vec4(float x_, float y_, float z_, float d_);

	//Handy methods
	void Add(Vec4 b);
	void Subtract(Vec4 b);
	void ScalarMultiplication(float s);
	float Mag();
	void Normalize();
	float Dot(Vec4);
	float Cross(Vec4);
	void Lerp(Vec4, float t);
	void RotateZ(float angle);

	Vec4 operator + (const Vec4& v) const;
	Vec4 operator - (const Vec4& v)const;
};

#endif