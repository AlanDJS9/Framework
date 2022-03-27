#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vec3.h"
#include "VMath.h"

using namespace std;
using namespace MATH;

using namespace MATH;

class PhysicsObject {
private:
	float mass, rotationalInertia;
	Vec3 position, velocity, acceleration, force;
	float angle, angularVel, angularAcc, angularDis, radius;
public:

	PhysicsObject();
	PhysicsObject(float mass_, float rotationalInertia_);
	//~
	void setMass(float mass);
	void setRotationalInertia(float rotationalInertia);
	void setRadius(const float radius_) { radius = radius_; }
	void setAngle(float angle_) { angle += angle_; }

	void setPosition(Vec3 position_) { position = position_; }
	void setVelocity(Vec3 velocity_) { velocity = velocity_; }
	void setAcceleration(Vec3 acceleration_) { acceleration = acceleration_; }
	void setForce(Vec3 force_) { force = force_; }

	void setAngularPosition(float angularPosition_) { angularDis = angularPosition_; }
	void setAngularVelocity(float angularVelocity_) { angularVel = angularVelocity_; }
	void setAngularAcceleration(float angularAcceleration_) { angularAcc = angularAcceleration_; }

	float getMass() { return mass; }
	float getRotationalInertia() { return rotationalInertia; }
	double getAngle() { return angle; }
	double getRadius() { return radius; }

	Vec3 getPosition() { return position; }
	Vec3 getVelocity() { return velocity; }
	Vec3 getAcceleration() { return acceleration; }
	Vec3 getForce() { return force; }


	float getAngularDisplacement() { return angularDis; }
	float getAngularVelocity() { return angularVel; }
	float getAngularAcceleration() { return angularAcc; }

};

#endif
