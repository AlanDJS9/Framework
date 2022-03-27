#pragma once
#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <math.h>
#include "Vector.h"

using namespace std;

class Ray
{
public:
	//Class variables
	Vec3 start;
	Vec3 dir;

	//Constructor
	Ray();
	Ray(Vec3 start_, Vec3 dir_);

	//Method to calculate the position
	Vec3 currentPosition(float t);

};

#endif