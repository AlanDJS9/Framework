#include "Scene6.h"
#include <SDL.h> 
#include <SDL_image.h>
#include "VMath.h"
#include "Randomizer.h"
#define PI 3.14159265

using namespace MATH;
using namespace std;

Scene6::Scene6(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene6 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene6 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 40.0f, 0.0f, 40.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	space = new Body(Vec3(0.0f, 35.0f, 0.0f));

						//x,y,mass
	star1 = new Body(Vec3(5.0f, 10.0f, 100.0f));
	star2 = new Body(Vec3(15.0f, 25.0f, 150.0f));


}

Scene6::~Scene6() {
	delete star1;
	delete star2;
	delete space;
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	if (renderer) SDL_DestroyRenderer(renderer);
}

bool Scene6::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;
	Matrix4 invProjection = MMath::inverse(projectionMatrix);



	image = IMG_Load("textures/earth.png");
	cliffTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	}
	SDL_FreeSurface(image);

	image = IMG_Load("textures/earth.png");
	marsTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		cout << "ERROR: Can´t load image";
		return false;
	}
	SDL_FreeSurface(image);

	image = IMG_Load("textures/futurama.png");
	shipTexture = SDL_CreateTextureFromSurface(renderer, image);
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
	Vec3 sizePlanet = invProjection * Vec3(float(width), float(height),0.0f);
	star1->setRadius(sizePlanet.x / 2.0f);

	//Setting texture and radius for mars
	SDL_QueryTexture(marsTexture, nullptr, nullptr, &width, &height);
	// C-Cast to chanfe the type of the variable
	Vec3 sizeMars = invProjection * Vec3(float(width), float(height), 0.0f);
	star2->setRadius(sizeMars.x / 2.0f);

	//Setting texture and radius for ship
	SDL_QueryTexture(shipTexture, nullptr, nullptr, &width, &height);
	// C-Cast to chanfe the type of the variable
	Vec3 sizeShip = invProjection * Vec3(float(width), float(height), 0.0f);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->setRadius(sizeShip.x / 2.0f);
	}

	return true;
}

void Scene6::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene6::Update(const float deltaTime) {
	//planet->Update(deltaTime);
	star1->setMass(100.0f);
	star2->setMass(150.0f);
	float m1 = star1->getmass();
	float m2 = star2->getmass();

	if (objects.size() == 0)
	{
		return;
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(deltaTime);
	}

	for (int i = 0; i < objects.size() - 1; i++)
	{
		float distance = VMath::distance(star1->getPos(), objects[i]->getPos());
		float distance2 = VMath::distance(star2->getPos(), objects[i]->getPos());
		float mShip = objects[i]->getmass();

		//ASK SCOTT ABOUT THIS  
			
	
				//velocity vector Boulder
				float m1 = objects[i]->getmass();
				//velocity vector Boulder
				Vec3 lineOfAction = star1->getPos() - objects[i]->getPos();
				float forceMagnitud1 = (1.0f * m1 * mShip) / pow(distance, 2);
				Vec3 normal = VMath::normalize(lineOfAction);
				Vec3 fGravitys1(lineOfAction.x * normal.x, lineOfAction.y * normal.y,0.0f);
				
				//velocity vector star2
				Vec3 lineOfAction2 = star2->getPos() - objects[i]->getPos();
				float forceMagnitud2 = (1.0f * m2 * mShip) / pow(distance2, 2);
				Vec3 normal2 = VMath::normalize(lineOfAction2);
				Vec3 fGravitys2(lineOfAction2.x * normal2.x, lineOfAction2.y * normal2.y, 0.0f);


			
								
				float finalforcex = fGravitys1.x + fGravitys2.x;
				float finalforcey = fGravitys1.y + fGravitys2.y;
				Vec3 ForceGravityFinal(finalforcex, finalforcey, 0.0f);

				objects[i]->ApplyForce(ForceGravityFinal);
	}
		
}

void Scene6::HandleEvent(const SDL_Event& sdlEvent)
{
	Body* aNewObject;

	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_SPACE:
			cout << "- SPACEBAR" << endl;
			aNewObject = new Body(Vec3(rnd.rand(1.0f, 25.0f), rnd.rand(1.0f, 25.0f), 1.0f));
			aNewObject->setMass(1.0f);
			aNewObject->setVel(Vec3(2.9f, -2.0f, 0.0f));
			objects.push_back(aNewObject);
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


void Scene6::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	screenCoords = projectionMatrix * star1->getPos();
	//Ask for the height of the texture -cliff
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
	
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
		
	SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, star1 -> getAngle(), nullptr, SDL_FLIP_NONE);

	//--
	screenCoords = projectionMatrix * star2->getPos();
	//Ask for the height of the texture -cliff
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);

	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;

	SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, star2->getAngle(), nullptr, SDL_FLIP_NONE);
	//--
	//TEXTURES FOR SHIP 
	//--
	for (int i = 0; i < objects.size(); i++)
	{
		screenCoords = projectionMatrix * objects[i]->getPos();
		//Ask for the height of the texture -cliff
		SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);

		//Assign the w and h of the image as it is
		square.x = static_cast<int>(screenCoords.x); /// We must update this with C11 typecasting - SSF
		square.y = static_cast<int>(screenCoords.y);
		square.w = width;
		square.h = height;

		SDL_RenderCopyEx(renderer, shipTexture, nullptr, &square, objects[i]->getAngle(), nullptr, SDL_FLIP_NONE);
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
	SDL_RenderCopyEx(renderer, spaceTexture, nullptr, &square, 0.0f, nullptr, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - FlappyFallingWithInicialVelocity - n01487231"
