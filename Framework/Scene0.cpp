#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_; /// Scott will explain this some day ... maybe
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene5 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	balloon1 = new Body(Vec3(5.0f,10.0f,0.0f));
	balloon2 = new Body(Vec3(3.0f, 10.0f, 0.0f));
	menu = new Body(Vec3(0.0f, 15.0f, 0.0f));
	space = new Body(Vec3(10.0f, 15.0f, 0.0f));
}

Scene0::~Scene0(){
	delete balloon1;
	delete balloon2;
	delete menu;
	delete space;
}

bool Scene0::OnCreate() {
	IMG_Init(IMG_INIT_PNG);

	ballImage = IMG_Load("textures/ball.png");
	if (ballImage == nullptr) {
		std::cout << "Can't open image file\n";
		return false;
	}

	menuImage = IMG_Load("textures/menu.png");
	if (menuImage == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	} 

	spaceImage = IMG_Load("textures/space.png");
	if (spaceImage == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	}
	return true;
}

void Scene0::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene0::Update(const float deltaTime) {

	balloon1->Update(deltaTime);
	balloon2->Update(deltaTime);
}

void Scene0::HandleEvent(const SDL_Event& sdlEvent)
{

}

void Scene0::Render() const {
	// Clear the screen 
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0,127,127));

	Vec3 screenCoords;
	SDL_Rect square;

	screenCoords = projectionMatrix * balloon1->getPos();
	square.x = (int) screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int) screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(ballImage, nullptr, screenSurface, &square);
	///SDL_FillRect(screenSurface, &square, SDL_MapRGB(screenSurface->format,0, 255, 0));

	screenCoords = projectionMatrix * balloon2->getPos();
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(ballImage, nullptr, screenSurface, &square);

	//SDL_FillRect(screenSurface, &square, SDL_MapRGB(screenSurface->format, 255, 0, 0));
	screenCoords = projectionMatrix * menu->getPos();
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(menuImage, nullptr, screenSurface, &square);

	screenCoords = projectionMatrix * space->getPos();
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(spaceImage, nullptr, screenSurface, &square);


	SDL_UpdateWindowSurface(window);
}