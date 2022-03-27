#include "Scene2.h"
#include <SDL.h>
#include <SDL_image.h>
#define PI 3.14159265

using namespace std;
Scene2::Scene2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "SCENE2 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "SCENE2 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;


	cliff = new Body(Vec3(2.0f, 5.0f, 0.0f));
	flappy = new Body(Vec3(2.0f, 5.0f,  0.0f));
	flappy->setMass(2.0f);
	//Create flappy wih the values 
	//Body(float positionBody_, float heightBody_, float massBody_, float accGeneral_, float dragC_, float initialV_, float initialAngle_)
	//flappy = new Body(2.0f, 5.0f, 2.0f,0.0f,-0.2f,30.0f,27.0f);
}

Scene2::~Scene2() {
	delete flappy;
	delete cliff;
}

bool Scene2::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;

	image = IMG_Load("textures/futurama.png");
	//Catching if assets didnt load correctly
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} flappyTexture = SDL_CreateTextureFromSurface(renderer, image);


	image = IMG_Load("textures/cliff.png");
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} cliffTexture = SDL_CreateTextureFromSurface(renderer, image);

	return true;
}

void Scene2::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene2::Update(const float deltaTime) {
	Vec3 gravityForce(0.0f, -9.81f * flappy->mass,0.0f );
	flappy->setVel(Vec3((30.0f * cos((27 * PI / 180))), (30.0f * sin((27 * PI / 180))),0.0f));
	Vec3 windForce(-30.0f,0.0f,0.0f);
	Vec3 dragForce = -0.2f * flappy->vel;
	Vec3 netForce = gravityForce + windForce + dragForce;
	flappy->ApplyForce(netForce);
	flappy->Update(deltaTime);
}

void Scene2::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			cout << "- up" << endl;
			flappy->setVel(Vec3(0.0f, 10.0f, 0.0f));
			break;
		case SDLK_DOWN:
			cout << "- down" << endl;
			flappy->setVel(Vec3(10.5f, 0.0f, 0.0f));
			break;
		default:
			break;

		}
		cout << "- KEYDOWN" << endl;

	}
	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)

	{
		cout << "- GAME ACTIVATED" << endl;
		//flappy->setAccel(Vec3(0.0f, -9.81f, 0.0f));
		//flappy->setVel(Vec3(5.0f, 0.0f, 0.0f));
	}
	//cout << "- Event hapenned" << endl;

}


void Scene2::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	screenCoords = projectionMatrix * cliff->getPos();
	//Ask for the height of the texture -cliff
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * flappy->getPos();
	//Ask for the height of the texture -flappy
	SDL_QueryTexture(flappyTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, flappyTexture, nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - FlappyFallingWithInicialVelocity - n01487231"
