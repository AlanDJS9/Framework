#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "SCENE1 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "SCENE1 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	space = new Body(Vec3(0.0f, 15.0f, 0.0f));

	cliff = new Body(Vec3(0.0f, 15.0f, 0.0f));
	flappy = new Body(Vec3(1.5f, 14.0f, 0.0f));
	
}

Scene1::~Scene1(){
	delete flappy;
	delete cliff;
	delete space;
}

bool Scene1::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;
	
	image = IMG_Load("textures/flappybird1.png");
	//Catching if assets didnt load correctly
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} flappyTexture = SDL_CreateTextureFromSurface(renderer,image);

	
	image = IMG_Load("textures/cliff.png");
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} cliffTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("textures/space.png");
	spaceTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load space image";
		return false;
	}

	return true;
}

void Scene1::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene1::Update(const float deltaTime) {

	cliff->Update(deltaTime);
	cout << flappy->getVel() << endl;
	
	flappy->Update(deltaTime);
}

void Scene1::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym) 
		{
		case SDLK_SPACE:
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
		flappy->setAccel(Vec3(0.0f, -9.81f, 0.0f));
		flappy->setVel(Vec3(5.0f, 0.0f, 0.0f));
	}
	//cout << "- Event hapenned" << endl;

}


void Scene1::Render()const {
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
	square.x = (int) screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int) screenCoords.y;
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
	//render space image
	screenCoords = projectionMatrix * space->getPos();
	//Ask for the height of the texture -cliff
	SDL_QueryTexture(spaceTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, spaceTexture, &square, &square, 0.0f, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);

}//Alan Jimenez - Programming GAME 101 -  Assignment 1 - FlappyFalling - n01487231"