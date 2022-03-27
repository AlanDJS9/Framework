#include "Physics.h"

#include <iostream>

void Physics::SimpleNewtonMotion(PhysicsObject& object_,  float deltaTime) {

	object_.setPosition(object_.getPosition() + object_.getVelocity() * deltaTime +( 0.5f * object_.getAcceleration() * deltaTime * deltaTime));
	object_.setVelocity(object_.getVelocity() + object_.getAcceleration() * deltaTime);
	
}

void Physics::RigidBodyRotation(PhysicsObject& object,  float deltaTime) {

	object.setAngularPosition(object.getAngularDisplacement() + object.getAngularVelocity() * deltaTime + 0.5f * object.getAngularAcceleration() * deltaTime *deltaTime);
	object.setAngularVelocity(object.getAngularVelocity() + object.getAngularAcceleration() * deltaTime);
	object.setAngle(object.getAngularDisplacement());
}

void Physics::applyTorque( float torque, PhysicsObject& object_) {

	object_.setAngularAcceleration(torque / object_.getRotationalInertia());
	//object_.setForce(Vec3(((object_.getForce().x) * cos(object_.getAngularDisplacement()) - (object_.getForce().y * sin(object_.getAngularDisplacement()))), ((object_.getForce().x) * sin(object_.getAngularDisplacement()) + ((object_.getForce().y) * cos(object_.getAngularDisplacement()))), 0.0));

}

void Physics::applyForce( Vec3 force_, PhysicsObject& object_) {
	object_.setForce(Vec3(((force_.x) * cos(object_.getAngularDisplacement()) - (force_.y * sin(object_.getAngularDisplacement()))), ((force_.x) * sin(object_.getAngularDisplacement()) + ((force_.y) * cos(object_.getAngularDisplacement()))), 0.0));
	object_.setAcceleration(force_ / object_.getMass());
	//printf("Acceleration -> %f, %f, %f *", ((force_ / object_.getMass())).x);
}

