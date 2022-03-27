
#include "Scene02.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Physics.h"
#include "Printer.h"

#define PI 3.14159265

using namespace std;

Scene02::Scene02(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene 01 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene 01 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 25000.0f, -5000.0f,5000.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;


	Vec3 resultantForce = Vec3(5e7, 0.0f, 0.0f);; //FORCE OF BOTH ENGINES 
	Vec3 resultantTorque = Vec3(6.291e8, 0.0f, 0.0f); //TORQUE


	spaceShip = new PhysicsObject(1e6, 2.67e10);
	Physics::applyForce(resultantForce, *spaceShip);
}

Scene02::~Scene02() {
	delete[] spaceShip;
}

bool Scene02::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;

	//image = IMG_Load("textures/futurama.png");
	image = IMG_Load("textures/LittleSpaceShip.png");

	Matrix4 invProjection = MMath::inverse(projectionMatrix);
	spaceShipTexture = SDL_CreateTextureFromSurface(renderer, image);
	//Catching if assets didnt load correctly
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} 
	int width, height;
	SDL_QueryTexture(spaceShipTexture, nullptr, nullptr, &width, &height);
	// C-Cast to change the type of the variable
	Vec3 size = invProjection * Vec3(float(width), float(height), 0.0f);
	size.print();
	spaceShip->setRadius(size.x / 2.0f);

	return true;
}

void Scene02::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene02::Update(const float deltaTime_) {
	Vec3 resultantForce = Vec3(5e7, 0.0f, 0.0f);; //FORCE OF BOTH ENGINES 
	Vec3 resultantTorque = Vec3(6.291e8, 0.0f, 0.0f); //TORQUE


	if (elapsedTime >= 5.0f && elapsedTime < 35.0f)
	{
		Physics::applyTorque(6.291e8, *spaceShip);
		Physics::applyForce(resultantForce/2, *spaceShip);
	}

	if (elapsedTime >= 35.0f) {
		Physics::applyTorque(0.0, *spaceShip);
		Physics::applyForce(Vec3(0.0, 0.0, 0.0), *spaceShip);
	}

	Physics::SimpleNewtonMotion(*spaceShip, deltaTime_);
	Physics::RigidBodyRotation(*spaceShip, deltaTime_);

	elapsedTime += deltaTime_;

	printf("| t = %f s | angularAcc = %f s | angularVel = %f s | angularDis = %f s | force.x = %f s | force.y = %f s | acc.x = %f s | acc.y = %f s | vel.x = %f s | vel.y = %f s | pos.x = %f m |  pos.y = %f m/s | \n", elapsedTime,spaceShip->getAngularAcceleration(), spaceShip->getAngularVelocity(), spaceShip->getAngularDisplacement(), 		spaceShip->getForce().x, spaceShip->getForce().y, spaceShip->getAcceleration().x, spaceShip->getAcceleration().y, spaceShip->getVelocity().x, spaceShip->getVelocity().y, spaceShip->getPosition().x, spaceShip->getPosition().y);
	timeArray.push_back(elapsedTime);
	AngAccelArray.push_back(spaceShip->getAngularAcceleration());
	AngVelArray.push_back(spaceShip->getAngularVelocity());
	AngleArray.push_back(spaceShip->getAngularDisplacement());
	ForceXArray.push_back(spaceShip->getForce().x);
	ForceYArray.push_back(spaceShip->getForce().y);
	AccelXArray.push_back(spaceShip->getAcceleration().x);
	AccelYArray.push_back(spaceShip->getAcceleration().y);
	VelXArray.push_back(spaceShip->getVelocity().x);
	VelYArray.push_back(spaceShip->getVelocity().y);
	PosXArray.push_back(spaceShip->getPosition().x);
	PosYArray.push_back(spaceShip->getPosition().y);

	if (elapsedTime > 40.0f) { //The cre stop the engine to fix another one but spaceship keeps rotating
		Physics::applyTorque(0.0, *spaceShip); 
		Physics::applyForce(Vec3(0.0, 0.0, 0.0), *spaceShip);

		Printer::Print(
			timeArray,
			AngAccelArray,
			AngVelArray,
			AngleArray,
			ForceXArray,
			ForceYArray,
			AccelXArray,
			AccelYArray,
			VelXArray,
			VelYArray,
			PosXArray,
			PosYArray
		);
	}
	//printf("\n Alan Jimenez - Physics II -  Assignment1/PART d - n01487231");
}

void Scene02::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			cout << "- up" << endl;
			Printer::Print(
				timeArray, 
				AngAccelArray, 
				AngVelArray,
				AngleArray,
				ForceXArray,
				ForceYArray,
				AccelXArray,
				AccelYArray,
				VelXArray,
				VelYArray,
				PosXArray,
				PosYArray
			);


			break;
		case SDLK_DOWN:
			cout << "- down" << endl;
		
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


void Scene02::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	screenCoords = projectionMatrix * spaceShip->getPosition();
	//Ask for the height of the texture -spaceShip
	SDL_QueryTexture(spaceShipTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spaceShipTexture, nullptr, &square,spaceShip ->getAngle(), nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - spaceShipFallingWithInicialVelocity - n01487231"
