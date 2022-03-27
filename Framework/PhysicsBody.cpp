#include "PhysicsBody.h"
#include "Vector.h"
#include <iostream>
#define PI 3.14159265
using namespace std;
using namespace MATH;


PhysicsBody::PhysicsBody()
{
	// Set pos, vel, and acc to [0, 0, 0]
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	vel.x = 0;
	vel.y = 0;
	vel.z = 0;

	acc.x = 0;
	acc.y = 0;
	acc.z = 0;

	// Set mass to a default value of 1.0f
	mass = 1.0f;
	radius = 1.0f;
	angle = 0.0;

}

PhysicsBody::PhysicsBody(float mass_, float rotationalInertia_)
{
	pos.x = 10.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	vel.x = 0.0;
	vel.y = 0.0;
	vel.z = 0.0;

	acc.x = 0.0;
	acc.y = 0.0;
	acc.z = 0.0;

	mass = mass_;
	rotationalInertia = rotationalInertia_;
	angle = 1.0;
	radius = 1.0f;


}

void PhysicsBody::Update(float deltaTime)
{
	float radianToDegrees = 360.0f / 2.0f * M_PI;
	float circumference = 2.0f * M_PI * radius;
	angle += radianToDegrees * vel.x * deltaTime / circumference;

	//WE CALCULATE THE ANGULAR VELOCITY HERE

	if (angularAcc != 0) //THIS IF HELPS IN CASE THE ANGULAR ACC = 0
	{
		//CALCULATING THE ANGULAR DISPLACEMENT
		angularDis = angularDis + (angularVel * deltaTime) + (0.5 * angularAcc * pow(deltaTime, 2));
		//((angularVel * angularVel) - (initialAngularVel * initialAngularVel)) / (2.0 * angularAcc);
	}
	angularVel = angularVel + (angularAcc * deltaTime);

	printf("| t = %f s | angularAcc = %f s | angularVel = %f s | angularDis = %f s | force.x = %f s | force.y = %f s | acc.x = %f s | acc.y = %f s | vel.x = %f s | vel.y = %f s | pos.x = %f m |  pos.y = %f m/s | \n", timeElapsed, angularAcc, angularVel, angularDis, force.x, force.y, acc.x, acc.y, vel.x, vel.y, pos.x, pos.y);



	//UPDATING LINEAR STUFF, POSITION, VELOCITY, ACCELERATION 
	force = Vec3(((force.x) * cos(angularDis) - (force.y * sin(angularDis))), ((force.x) * sin(angularDis) + ((force.y) * cos(angularDis))), 0.0);
	acc = Vec3(force.x / mass, force.y / mass, 0.0);

	pos.x += vel.x * deltaTime + 0.5f * acc.x * deltaTime * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * acc.y * deltaTime * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * acc.z * deltaTime * deltaTime;
	vel.y += acc.y * deltaTime;
	vel.x += acc.x * deltaTime;

	//SECONDS ELAPSED
	timeElapsed += deltaTime;
}


//printf("\n Alan Jimenez - Physics II -  Assignment1/PART B - n01487231");

