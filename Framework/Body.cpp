#include "Body.h"
#define PI 3.14159265

using namespace std;

Body::Body(){
	pos.x = 2.0f;
	pos.y = 12.5f;
	pos.z = 0.0f;

	vel.x = 15.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = -9.81f;
	accel.z = 0.0f;

	mass = 1.0f;
	radius = 1.0f;
	angle = 1.0;
}
Body::Body(Vec3 pos_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;


	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;


	//mass = pos_.z;
	mass = 1.0F;
	radius = 1.0f;
	angle = 1.0;
	c = 1.0f;
}

Body::~Body(){
	
}

void Body::Update(float deltaTime){

	float radianToDegrees = 360.0f / 2.0f * M_PI;
	float circumference = 2.0f * M_PI * radius;
	angle += radianToDegrees * vel.x * deltaTime / circumference;

	pos.x += vel.x * deltaTime + 0.5f * accel.x * deltaTime * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * accel.y * deltaTime * deltaTime;
	vel.x += accel.x * deltaTime;
	vel.y += accel.y * deltaTime;
	///Floor collision
	if (pos.y < 2.0f) {
		vel.y *= -1.0f;
		pos.y = 2.0f;
		
	}
	// roof
	if (pos.y > 15.0f) {
		vel.y *= -1.0f;
		pos.y = 15.0f;
		//Change vel on x to make the jump 'feel'
		vel.x = 3.0f;
	}
	// Right wall
	if (pos.x > 28.0f) {
		vel.x = -vel.x;
		pos.x = 28.0f;
	}
	// Left wall
	if (pos.x < 0.0f) {
		vel.x = -vel.x;
		pos.x = 0.0f;
	}
	printf("| time = %f s | y_pos = %f m |  y_vel =%f m/s | y_acc = %f s^2 \n", deltaTime, pos.y, vel.y, accel.y);

	
}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - FlappyFallingWithInicialVelocity - n01487231"

void Body::ApplyForce(Vec3 force)
{
	accel = force/mass;
}
