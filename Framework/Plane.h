#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <math.h>
#include "Vector.h"

#include "Ray.h"

using namespace std;

class Plane
{
public:
	//Class variables
	Vec4 plane;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float d = 0.0f;

	Plane();

	//Constructor
	Plane(float x_, float y_, float z_, float d_);
	Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2);

	//Method to calculate the position
	Vec3 intersectionPoint(Ray ray);
	Plane(Vec3 normal, Vec3 p);
	Plane(Vec3 normal, float _d);
	void set(float x, float y, float z, float d);
	void print();

};

#endif