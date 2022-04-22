
#include "Scene03.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Physics.h"
#include "Printer.h"

#define PI 3.14159265

using namespace std;

Scene03::Scene03(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene 01 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene 03 COLLISIONS ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Dynamic sphere with static sphere (ie a ball bouncing off a fixed sphere)
	crazySphereA = new PhysicsObject(Vec3(15.0f, 5.5f, 0.0f));
	staticSphere = new PhysicsObject(Vec3(0.0f, 5.0f, 0.0f));

	//Dynamic sphere with static wall(ie a ball bouncing off a fixed plane)
	crazySphereB = new PhysicsObject(Vec3(-2.0f, 10.0f, 0.0f));
	plane = new Plane(-1.0f,1.0f,0.0f,0.0f);

	//Dynamic sphere with dynamic sphere with elasticity
	crazySphereC = new PhysicsObject(Vec3(10.0f, 5.5f, 0.0f));
	crazySphereD = new PhysicsObject(Vec3(0.0f, 5.0f, 0.0f));
}

Scene03::~Scene03() {
	delete[] staticSphere, crazySphereA, crazySphereB, crazySphereC, crazySphereD, plane;
}

bool Scene03::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;

	//image = IMG_Load("textures/futurama.png");
	image = IMG_Load("textures/ball.png");

	Matrix4 invProjection = MMath::inverse(projectionMatrix);
	spheresTexture = SDL_CreateTextureFromSurface(renderer, image);
	//Catching if assets didnt load correctly
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} 
	int width, height;
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	// C-Cast to change the type of the variable
	Vec3 size = invProjection * Vec3(float(width), float(height), 0.0f);

	staticSphere->setRadius(size.x / 2.0f);
	crazySphereA->setRadius(size.x / 2.0f);
	crazySphereB->setRadius(size.x / 2.0f);
	crazySphereC->setRadius(size.x / 2.0f);
	crazySphereD->setRadius(size.x / 2.0f);

	return true;
}

void Scene03::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene03::Update(const float deltaTime_) {
	Physics::SimpleNewtonMotion(*staticSphere, deltaTime_);
	Physics::SimpleNewtonMotion(*crazySphereA, deltaTime_);
	Physics::SimpleNewtonMotion(*crazySphereB, deltaTime_);
	Physics::SimpleNewtonMotion(*crazySphereC, deltaTime_);
	Physics::SimpleNewtonMotion(*crazySphereD, deltaTime_);

	Physics::RigidBodyRotation(*staticSphere, deltaTime_);
	Physics::RigidBodyRotation(*crazySphereA, deltaTime_);
	Physics::RigidBodyRotation(*crazySphereB, deltaTime_);
	Physics::RigidBodyRotation(*crazySphereC, deltaTime_);
	Physics::RigidBodyRotation(*crazySphereD, deltaTime_);

	if (Physics::SphereSphereCollisionDetected(*staticSphere, *crazySphereA)==true)
	{
		Physics::SphereStaticSphereCollisionResponse(*crazySphereA, *staticSphere);
	}

	if (Physics::SphereSphereCollisionDetected(*crazySphereC, *crazySphereD)==true)
	{
		Physics::SphereSphereCollisionResponse(*crazySphereC, *crazySphereD);
	}

	if (Physics::SpherePlaneCollisionDetected(*crazySphereB, *plane)==true)
	{
		std::cout << "hit plane" << std::endl;
		Physics::SpherePlaneCollisionResponse(*crazySphereB, *plane);
	}

	elapsedTime += deltaTime_;

	//printf("\n Alan Jimenez - Physics II -  Assignment1/PART d - n01487231");
}

void Scene03::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			cout << "-SPHERE-STATICSPHERE" << endl;
			crazySphereA->setVelocity(Vec3(-5.0f, 0.0f, 0.0f));
			staticSphere->setVelocity(Vec3(0.0f, 0.0f, 0.0f));

			break;
		case SDLK_DOWN:
			cout << "- SPHERE-PLANE" << endl;
			crazySphereB->setVelocity(Vec3(5.0f, 0.0f, 0.0f));
			break;
		case SDLK_LEFT:
			cout << "- SPHERE-SPHERE" << endl;
			crazySphereC->setVelocity(Vec3(-10.0f, 0.0f, 0.0f));
			crazySphereD->setVelocity(Vec3(8.0f, 0.0f, 0.0f));
			break;
		default:
			break;

		}
		cout << "- KEYDOWN" << endl;

	}
	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)

	{
		cout << "- GAME ACTIVATED" << endl;
	}

}


void Scene03::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	screenCoords = projectionMatrix * staticSphere->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spheresTexture, nullptr, &square, staticSphere->getAngle(), nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * crazySphereA->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spheresTexture, nullptr, &square, crazySphereA->getAngle(), nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * crazySphereB->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spheresTexture, nullptr, &square, crazySphereB->getAngle(), nullptr, SDL_FLIP_NONE);


	screenCoords = projectionMatrix * crazySphereC->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spheresTexture, nullptr, &square, crazySphereC->getAngle(), nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * crazySphereD->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spheresTexture, nullptr, &square, crazySphereD->getAngle(), nullptr, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(renderer, 700, 30, 50, 700);

	SDL_RenderPresent(renderer);

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - spaceShipFallingWithInicialVelocity - n01487231"
