#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <math.h>

using namespace std;

class Vec3
{
public:
	//Class variables
	float x;
	float y;
	float z;
	//Construct
	Vec3();
	Vec3(float x_, float y_, float z_);

	//Handy methods
	void Add(Vec3 b);
	void Subtract(Vec3 b);
	void ScalarMultiplication(float s);
	float Mag();
	void Normalize();
	float Dot(Vec3);
	Vec3 Cross(Vec3);
	void Lerp(Vec3, float t);
	void RotateZ(float angle);

	Vec3 operator + (const Vec3& v) const;
	Vec3 operator - (const Vec3& v)const;

};

#endif