#ifndef PHYSICS_H
#define PHYSICS_H
#include "PhysicsObject.h"
#include "Plane.h"

class Physics {
	public:
	static void SimpleNewtonMotion(PhysicsObject& object, const float deltaTime);
	static void RigidBodyRotation(PhysicsObject& object, const float deltaTime);

	static void applyTorque(const float torque, PhysicsObject& object);
	static void applyForce(const Vec3 force, PhysicsObject& object);


	// Collision detection methods:
	static bool SphereSphereCollisionDetected(const PhysicsObject& PhysicsObject1, const PhysicsObject& PhysicsObject2);
	static bool SpherePlaneCollisionDetected(const PhysicsObject& PhysicsObject1, const Plane& plane);
		// Collision response methods:
	static void SphereSphereCollisionResponse(PhysicsObject& PhysicsObject1, PhysicsObject& PhysicsObject2);
	static void SphereStaticSphereCollisionResponse(PhysicsObject& PhysicsObject1, const PhysicsObject& staticSphere);
	static void SpherePlaneCollisionResponse(PhysicsObject& PhysicsObject1, const Plane& plane);
};

#endif