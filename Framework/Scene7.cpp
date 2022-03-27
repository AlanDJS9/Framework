#include "Scene7.h"
#include <SDL.h> 
#include <SDL_image.h>
#include "VMath.h"
#include "Randomizer.h"
using namespace MATH;
using namespace std;
Scene7::Scene7(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene7 ERROR: Can´t create renderer ";
	}

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene7 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	space = new Body(Vec3(0.0f, 15.0f, 0.0f));

	
	
}

Scene7::~Scene7() {

	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	delete space;
}

bool Scene7::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;
	image = IMG_Load("textures/ball.png");
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

void Scene7::OnDestroy() {
	if (renderer) SDL_DestroyRenderer(renderer);

}

void Scene7::Update(const float deltaTime) {
	//Show off -> static cast
	
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
		for (int j = i + 1; j < objects.size(); j++)
		{
			float distance = VMath::distance(objects[i]->getPos(), objects[j]->getPos());
			//ASK SCOTT ABOUT THIS  
			if (distance <= objects[i]->getRadius() + objects[j]->getRadius())
			{
				//cout << "Collision" << endl;
				//velocity vector Boulder
				Vec3 v1 = objects[i]->getVel();
				float m1 = objects[i]->getmass();
				//velocity vector Boulder
				Vec3 v2 = objects[j]->getVel();
				float m2 = objects[j]->getmass();
				// coeficient of restitution a.k.a bounciness
				float e = 1.0f;

				Vec3 lineOfActtion = objects[i]->getPos() - objects[j]->getPos();
				Vec3 normal = VMath::normalize(lineOfActtion);

				//dot product of velocity vector . normalized lineOfAction
				float vp1 = VMath::dot(v1, normal); //Scott drawing
				float vp2 = VMath::dot(v2, normal);
				//If  + the ball are flying away if negative they are approching each other
				if ((vp1 - vp2) > 0.0f) { return; }

				float v1pp = (m1 - e * m2) * vp1 + (1.0f * e) * m2 * vp2 / (m1 + m2);
				float v2pp = (m2 - e * m1) * vp2 + (1.0f * e) * m1 * vp1 / (m1 + m2);

				Vec3 v1new = v1 + (v1pp - vp1) * normal;
				Vec3 v2new = v2 + (v2pp - vp2) * normal;
				v1new.print();
				v2new.print();

				objects[i]->setVel(v1new);
				objects[j]->setVel(v2new);
			}
			else {
				//cout << "nada" << endl;
			}
		}
	}
}

void Scene7::HandleEvent(const SDL_Event& sdlEvent)
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
		printf("%f %f", pos.x, pos.y);
	}

}


void Scene7::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

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

		SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, objects[i]->getAngle(), nullptr, SDL_FLIP_NONE);
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

}	//Alan Jimenez - Programming GAME 105 -  Assignment 3AB - FlappyFallingWithInicialVelocity - n01487231"
