#include "Scene3.h"
#include <SDL.h> 
#include <SDL_image.h>
using namespace std;

Scene3::Scene3(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene3 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene3 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	space = new Body(Vec3(0.0f, 15.0f, 0.0f));

	boulder = new Body(Vec3(0.0f, 2.1f, 0.0f));
}

Scene3::~Scene3() {
	delete boulder;
	delete space;

}

bool Scene3::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;



	image = IMG_Load("textures/ball.png");
	Matrix4 invProjection = MMath::inverse(projectionMatrix);
	cliffTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	}

	image = IMG_Load("textures/space.png");
	spaceTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load space image";
		return false;
	}
	int width, height;
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
	// C-Cast to chanfe the type of the variable
	Vec3 size = invProjection * Vec3(float(width), float(height),0.0f);
	size.print();
	boulder->setRadius(size.x / 2.0f);
	return true;
}

void Scene3::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene3::Update(const float deltaTime) {
	//Show off -> static cast
	boulder->Update(deltaTime);
}

void Scene3::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_SPACE:
			cout << "- up" << endl;
			boulder->setVel(Vec3(3.0f, 0.0f, 0.0f));
			break;
		case SDLK_DOWN:
			cout << "- down" << endl;
			boulder->setVel(Vec3(10.5f, 0.0f, 0.0f));
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


void Scene3::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;
	screenCoords = projectionMatrix * boulder->getPos();
	//Ask for the height of the texture -cliff
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
	
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
		
	SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, boulder -> getAngle(), nullptr, SDL_FLIP_NONE);
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

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - FlappyFallingWithInicialVelocity - n01487231"
