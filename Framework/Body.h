#ifndef BODY_H
#define BODY_H
#include "Vector.h"

using namespace MATH;

class Body {
public: 
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	float radius;
	float c;
	float dragC = -2.0f;
	double angle;


public:
	Body();
	Body(Vec3 pos_);
	Body(float positionBody_, float heightBody_, float massBody_, float accGeneral_, float dragC_, float initialV_, float initialAngle_);

	~Body();
	void Update(float deltaTime);
	void ApplyForce(Vec3 force);
	Vec3 getVel() {return vel;}
	Vec3 getPos() { return pos; }
	float getmass() { return mass; }

	void setAccel(const Vec3& accel_)
	{
		accel.x = accel_.x;
		accel.y = accel_.y;
		accel.z = accel_.z;
	}
	void setVel(const Vec3& vel_)
	{
		vel.x = vel_.x;
		vel.y = vel_.y;
		vel.z = vel_.z;
	}
	float getRadius() { return radius; }
	void setRadius(const float radius_) { radius = radius_; }
	void setMass(const float mass_) { mass = mass_; }

	double getAngle() { return angle; }
	double getC() { return c; }

};

#endif