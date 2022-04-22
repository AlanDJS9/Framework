#include "Physics.h"
#include "Plane.h"
#include <iostream>

void Physics::SimpleNewtonMotion(PhysicsObject& object_,  float deltaTime) {

	object_.setPosition(object_.getPosition() + object_.getVelocity() * deltaTime +( 0.5f * object_.getAcceleration() * deltaTime * deltaTime));
	object_.setVelocity(object_.getVelocity() + object_.getAcceleration() * deltaTime);

}

void Physics::SimpleVerletMotion(PhysicsObject& object_, float deltaTime) {

	object_.setPosition(object_.getPosition() + object_.getVelocity() * deltaTime + (0.5f * object_.getPreviusAcceleration() * deltaTime * deltaTime));
	object_.setVelocity(object_.getVelocity() + 0.5f * (object_.getPreviusAcceleration() + object_.getAcceleration()) * deltaTime);

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
	object_.setForce(Vec3(((force_.x) * cos(object_.getAngularDisplacement()) + (force_.y * -sin(object_.getAngularDisplacement()))), ((force_.x) * sin(object_.getAngularDisplacement()) + ((force_.y) * cos(object_.getAngularDisplacement()))), 0.0));
	object_.setAcceleration(force_ / object_.getMass());
	//printf("Acceleration -> %f, %f, %f *", ((force_ / object_.getMass())).x);
}

float volumeInWaterF(PhysicsObject& object_, float waterHeight) {
	float volume = 0.0f;
	float theta = (2 * acosf(object_.getMass() / object_.getRadius()));
	if (object_.getPosition().y - object_.getRadius() <= waterHeight && object_.getPosition().y >= waterHeight) {//Waterline below the cylinder center
		return volume = 0.5f * pow(object_.getRadius(), 2) * (theta - sinf(theta)) * object_.getLenght();

	}else if (object_.getPosition().y <= waterHeight) {//Waterline is above the centre
		return volume = M_PI * pow(object_.getRadius(), 2) * object_.getLenght() - (0.5f * pow(object_.getRadius(), 2) * (theta - sinf(theta)) * object_.getLenght());
	}
	else if (object_.getPosition().y + object_.getRadius() <= waterHeight) {//Completly  sumerged
		return volume = M_PI * pow(object_.getRadius(), 2) * object_.getLenght();
	}
	else if ((object_.getPosition().y - object_.getRadius()) > waterHeight) {//Log out of water
		return volume = 0.0f;
	}
}

void Physics::applyAllForce(PhysicsObject& object_, float waterHeight) {
	const float gravity = 9.81f;
	const float dragC = 0.8f;
	const float liquidDensity = 4.0f;
	
	float volumeInWater = M_PI * pow(object_.getRadius(), 2) * object_.getLenght();

	Vec3 gravityForce = Vec3(0,object_.getMass() * -gravity , 0.0f);
	Vec3 dragForce = dragC * -object_.getVelocity() ;
	Vec3 bForce = Vec3(0, liquidDensity * gravity * volumeInWater, 0.0f);

	Vec3 netForce = gravityForce + dragForce + bForce;
	//SAVE PREVIUS ACCEL
	object_.setPreviusAcceleration(object_.getAcceleration());
	object_.setAcceleration(netForce / object_.getMass());
}

// Collision detection methods: //why const not work
bool Physics::SphereSphereCollisionDetected(const PhysicsObject &PhysicsObject1,  const PhysicsObject &PhysicsObject2){
	//checks the distance between spheres
	float sumObjectRadius = PhysicsObject1.getRadius() + PhysicsObject2.getRadius();
	float distanceBetweenObjects = VMath::mag((PhysicsObject1.getPosition() - PhysicsObject2.getPosition()));
	if (sumObjectRadius >= distanceBetweenObjects) {
		return true;//Spheres have collided
	}
	else return false;//Spheres haven't collided
}//why const not work

bool Physics::SpherePlaneCollisionDetected( PhysicsObject &PhysicsObject1,  Plane plane){
	//checks the distance between sphere and plane
	//distance = (plane normal) dot (PhysicsObject position) + d – PhysicsObject.radius
	float distanceBetweenObjectsPlane = (VMath::dot(Vec3(plane.plane.x, plane.plane.y, plane.plane.z), PhysicsObject1.getPosition())) + plane.plane.w - PhysicsObject1.getRadius();
	//float distanceBetweenObjectsPlane = ((p * PhysicsObject1.getPosition().x) + (plane.y * PhysicsObject1.getPosition().y) + (plane.z * PhysicsObject1.getPosition().z) + plane.d ) - PhysicsObject1.getRadius();
	if (PhysicsObject1.getRadius() >= distanceBetweenObjectsPlane) {
		return true;//Sphere collided
	}
	else return false;//Sphere didn't collided

}
// Collision response methods:
void Physics::SphereSphereCollisionResponse(PhysicsObject& PhysicsObject1, PhysicsObject& PhysicsObject2){
				//velocity vector Boulder
	Vec3 v1 = PhysicsObject1.getVelocity();
	float m1 = PhysicsObject1.getMass();
	//velocity vector Boulder
	Vec3 v2 = PhysicsObject2.getVelocity();
	float m2 = PhysicsObject2.getMass();
	// coeficient of restitution a.k.a bounciness
	float e = 1.0f;

	Vec3 lineOfActtion = (PhysicsObject1.getPosition() - PhysicsObject2.getPosition());
	Vec3 normal = VMath::normalize(lineOfActtion);

	//dot product of velocity vector . normalized lineOfAction
	float vp1 = VMath::dot(v1, normal); //Collision formula
	float vp2 = VMath::dot(v2, normal);
	//If  + the ball are flying away if negative they are approching each other
	if ((vp1 - vp2) > 0.0f) { return; }

	float v1pp = (m1 - e * m2) * vp1 + (1.0f * e) * m2 * vp2 / (m1 + m2);
	float v2pp = (m2 - e * m1) * vp2 + (1.0f * e) * m1 * vp1 / (m1 + m2);
	Vec3 v1new = v1 + (v1pp - vp1) * normal;
	Vec3 v2new = v2 + (v2pp - vp2) * normal;

	PhysicsObject1.setVelocity(v1new);
	PhysicsObject2.setVelocity(v2new);

}
	void Physics::SphereStaticSphereCollisionResponse(PhysicsObject& crazySphere1, const PhysicsObject& staticSphere){
	//How much does one sphere moves
		Vec3 nNormal = VMath::normalize(staticSphere.getPosition() - crazySphere1.getPosition());
		crazySphere1.setVelocity(crazySphere1.getVelocity() - 2 * VMath::dot(nNormal, crazySphere1.getVelocity()) * nNormal);

}
	void Physics::SpherePlaneCollisionResponse(PhysicsObject& PhysicsObject1, const Plane& plane){
	//How much does the sphere moves
		Vec3 normal = Vec3(plane.plane.x, plane.plane.y, plane.plane.z);
		Vec3 normalizedNormal = VMath::normalize(normal);
		float ProjectionMagnitude1 = VMath::dot(-PhysicsObject1.getVelocity(), normalizedNormal);
		Vec3 ProjectorVector = ProjectionMagnitude1 * normalizedNormal;
		PhysicsObject1.setVelocity(PhysicsObject1.getVelocity() + (2 * ProjectorVector));
}
