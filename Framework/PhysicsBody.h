#pragma once
//#include "Vec3e.h"
#include "Vector.h"
#include "VMath.h"
using namespace std;
using namespace MATH;

struct PhysicsBody
{
	//Class variables
	float mass = 0;//
	float timeElapsed = 0; 
	
	float rotationalInertia = 0;//
	float torque = 6.291e8;
	float angularVel = 0.;
	float angularAcc = 0;
	float angularDis = 0;
	float torqueForce = 0;
	float initialAngularVel = 0;
	float radius;
	double angle;//

	Vec3 pos;//
	Vec3 vel;//
	Vec3 acc;//
	Vec3 force;

	//Construct
	PhysicsBody();
	PhysicsBody(float mass_, float rotationalInertia_);
	PhysicsBody(Vec3 initialPos_);
	//Handy methods

	void applyTorque(Vec3 torque_) {
		angularAcc = torque_.x / rotationalInertia;
		force = Vec3(((force.x) * cos(angularDis) - (force.y * sin(angularDis))), ((force.x) * sin(angularDis) + ((force.y) * cos(angularDis))), 0.0);
	};
	void applyForce(Vec3 force_) {
		force = force_;
		acc = Vec3(force_.x / mass, force_.y / mass, 0.0);
	};

	void Update(const float deltaTime);
	
	float getTimeElapsed() { return timeElapsed; }

	//Setters and getters
	Vec3 getPos() { return pos; }
	float getRadius() { return radius; }
	void setRadius(const float radius_) { radius = radius_; }
	double getAngle() { return angle; }

};