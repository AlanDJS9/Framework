#include "Scene04.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Physics.h"
#include "Printer.h"

#define PI 3.14159265

using namespace std;

Scene04::Scene04(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene 01 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene 04 COLLISIONS ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	crazySphereA = new PhysicsObject(Vec3(15.0f, 5.5f, 0.0f));
	crazySphereA->setLenght(1.0f);
	//crazySphereA->setMass(1.0f);
}

Scene04::~Scene04() {
	delete[] staticSphere, crazySphereA, crazySphereB, crazySphereC, crazySphereD, plane;
}

bool Scene04::OnCreate() {
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

	crazySphereA->setRadius(size.x / 2.0f);
	

	return true;
}

void Scene04::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene04::Update(const float deltaTime_) {

	Physics::SimpleVerletMotion(*crazySphereA, deltaTime_);
	Physics::RigidBodyRotation(*crazySphereA, deltaTime_);


	//Physics::applyAllForce(*crazySphereA, 10.0f);

	elapsedTime += deltaTime_;
	printf("| t = %f s | angularAcc = %f s | angularVel = %f s | angularDis = %f s | force.x = %f s | force.y = %f s | acc.x = %f s | acc.y = %f s | vel.x = %f s | vel.y = %f s | pos.x = %f m |  pos.y = %f m/s | \n", elapsedTime, crazySphereA->getAngularAcceleration(), crazySphereA->getAngularVelocity(), crazySphereA->getAngularDisplacement(), crazySphereA->getForce().x, crazySphereA->getForce().y, crazySphereA->getAcceleration().x, crazySphereA->getAcceleration().y, crazySphereA->getVelocity().x, crazySphereA->getVelocity().y, crazySphereA->getPosition().x, crazySphereA->getPosition().y);

	//printf("\n Alan Jimenez - Physics II -  Assignment1/PART d - n01487231");
}

void Scene04::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			cout << "- Force activated" << endl;

			Physics::applyAllForce(*crazySphereA, 1.0f);
			break;
		case SDLK_DOWN:
			cout << "- SPHERE-PLANE" << endl;
			break;
		case SDLK_LEFT:
			cout << "- SPHERE-SPHERE" << endl;
			
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


void Scene04::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	
	screenCoords = projectionMatrix * crazySphereA->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spheresTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spheresTexture, nullptr, &square, crazySphereA->getAngle(), nullptr, SDL_FLIP_NONE);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(renderer, 500, 500, 30, 30);

	SDL_RenderPresent(renderer);

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - spaceShipFallingWithInicialVelocity - n01487231"
