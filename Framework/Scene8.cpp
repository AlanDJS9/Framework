#include "Scene8.h"
#include <SDL.h> 
#include <SDL_image.h>
#include "VMath.h"
#include "Randomizer.h"

using namespace MATH;
using namespace std;

Scene8::Scene8(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene8 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	cout << "Scene8 ACTIVATED" << endl;

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);

	space = new Body(Vec3(0.0f, 15.0f, 0.0f));


}

Scene8::~Scene8() {

	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	delete space;
}

bool Scene8::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;
	SDL_Surface* boulder;


	image = IMG_Load("textures/walk_spritesheet.png");
	boyTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	}
	SDL_FreeSurface(image);

	image = IMG_Load("textures/walk_spritesheet.png");
	cliffTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	}
	SDL_FreeSurface(image);

	image = IMG_Load("textures/space.png");
	spaceTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load space image";
		return false;
	}	SDL_FreeSurface(image);

	int width, height;
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
	// C-Cast to chanfe the type of the variable
	Vec3 size = invProjectionMatrix * Vec3(float(width), float(height),0.0f);
	size.print();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->setRadius(size.x / 2.0f);
	}
	
	return true;
}

void Scene8::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene8::Update(const float deltaTime) {
	//Show off -> static cast
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(deltaTime);
	}
	
}

void Scene8::HandleEvent(const SDL_Event& sdlEvent)
{
	Body* aNewObject;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_SPACE:
			cout << "- SPACEBAR" << endl;
			aNewObject = new Body(Vec3(rnd.rand(1.0f, 20.0f), rnd.rand(1.0f, 15.0f), 1.0f));
			aNewObject->setVel(Vec3(rnd.rand(1.0f, 5.0f), rnd.rand(1.0f, 5.0f), 0.0f));
			aNewObject->setAccel(Vec3(0.0f, -9.81f, 0.0f));
			objects.push_back(aNewObject);

			break;
		default:
			cout << "- KEYDOWNIF" << endl;

			break;

		}

	}
	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		Vec3 screenPos = Vec3(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 0.0f);
		Vec3 pos = invProjectionMatrix * screenPos;
		printf(" THE COORDINATES FROM THE MOUSE ARE (%f, %f)", pos.x, pos.y);
	}

}


void Scene8::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	static int frameCounter = 0;
	static int counter = 0;

	Vec3 screenCoords;
	SDL_Rect square;
	SDL_Rect boySquare;

	int width, height;


	for (int i = 0; i < objects.size(); i++)
	{
		frameCounter++;
		frameCounter %= 4;
		screenCoords = projectionMatrix * objects[i]->getPos();
		//Ask for the height of the texture -cliff
		SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
		boySquare.y = 0;
		boySquare.w = width/8;
		boySquare.h = height;
		boySquare.x = counter;
		
		if (counter >= width) 
		{
			counter = 0;
		}
		if(frameCounter == 0) {
			counter += width / 8;
		}
		//Assign the w and h of the image as it is
		square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
		square.y = (int)screenCoords.y;
		square.w = width / 8;
		square.h = height;

		if (objects[i]->getVel().x >= 0.0f) {
			SDL_RenderCopyEx(renderer, cliffTexture, &boySquare, &square, 0.0, nullptr, SDL_FLIP_NONE);
		}
		else {
			SDL_RenderCopyEx(renderer, cliffTexture, &boySquare, &square, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
		}
	}
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

}


