#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vector.h"
#include "VMath.h"

using namespace std;
using namespace MATH;

class PhysicsObject {
private:
	float mass, rotationalInertia;
	
public:
	Vec3 position, velocity, acceleration, force, previusAcceleration;

	float angle, angularVel, angularAcc, angularDis;
	 float radius,  lenght;

	PhysicsObject();
	PhysicsObject(float mass_, float rotationalInertia_);
	PhysicsObject(Vec3 initialV_, Vec3 initialPos_, float radius_);
	PhysicsObject(Vec3 initialPos_);

	//~
	void setMass(float mass);
	void setRotationalInertia(float rotationalInertia);
	void setAngle(float angle_) { angle += angle_; }

	void setPosition(Vec3 position_) { position = position_; }
	void setVelocity(Vec3 velocity_) { velocity = velocity_; }
	void setAcceleration(Vec3 acceleration_) { acceleration = acceleration_; }
	void setPreviusAcceleration(Vec3 previusAcceleration_) { previusAcceleration = previusAcceleration_; }

	void setForce(Vec3 force_) { force = force_; }
	void setRadius(float radius_) { radius = radius_; }
	void setLenght(float lenght_) { lenght = lenght_; }

	void setAngularPosition(float angularPosition_) { angularDis = angularPosition_; }
	void setAngularVelocity(float angularVelocity_) { angularVel = angularVelocity_; }
	void setAngularAcceleration(float angularAcceleration_) { angularAcc = angularAcceleration_; }

	float getMass() const { return mass; }
	float getRotationalInertia()const { return rotationalInertia; }
	double getAngle() const { return angle; }
	 double getRadius() const{ return radius; }
	 double getLenght() const { return lenght; }

	Vec3 getPosition() const { return position; }
	Vec3 getVelocity() const { return velocity; }
	Vec3 getAcceleration()const { return acceleration; }
	Vec3 getPreviusAcceleration()const { return previusAcceleration; }

	Vec3 getForce() const { return force; }


	float getAngularDisplacement() { return angularDis; }
	float getAngularVelocity() { return angularVel; }
	float getAngularAcceleration() { return angularAcc; }

};

#endif
