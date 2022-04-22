#include "PhysicsObject.h"
#include <iostream>
#define PI 3.14159265
using namespace std;
using namespace MATH;

PhysicsObject::PhysicsObject() {
	position.x = 0;
	position.y = 0;
	position.z = 0;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;

	// Set mass to a default value of 1.0f
	mass = 1.0f;
	radius = 1.0f;
	angle = 0.0;
	radius = 0.0f;
	angularVel = 0.0f;
	angularAcc = 0.0;
	angularDis = 0.0;
	rotationalInertia = 0;

}

PhysicsObject::PhysicsObject(Vec3 initialPos_){
	position.x = initialPos_.x;
	position.y = initialPos_.y;
	position.z = initialPos_.z;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;

	// Set mass to a default value of 1.0f
	mass = 10.0f;
	radius = 1.0f;
	angle = 0.0;
	radius = 0.0f;
	angularVel = 0.0f;
	angularAcc = 0.0;
	angularDis = 0.0;
	rotationalInertia = 0;

}

PhysicsObject::PhysicsObject(float mass_, float rotationalInertia_) {
	position.x = 100.0f;
	position.y = 100.0f;
	position.z = 0;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;

	mass = mass_;
	rotationalInertia = rotationalInertia_;
	angle = 0.0;
	radius = 0.0f;
	angularVel = 0.0;
	angularAcc = 0.0;
	angularDis = 0.0;
}

PhysicsObject::PhysicsObject(Vec3 initialV_, Vec3 initialPos_, float radius_)
{
	position.x = initialPos_.x;
	position.y = initialPos_.y;
	position.z = initialPos_.z;
	 
	velocity.x = initialV_.x;
	velocity.y = initialV_.y;
	velocity.z = initialV_.z;

	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;

	mass = 0.0f;
	rotationalInertia = 0.0f;
	angle = 0.0;

	radius = radius_;
	angularVel = 0.0;
	angularAcc = 0.0;
	angularDis = 0.0;
}
