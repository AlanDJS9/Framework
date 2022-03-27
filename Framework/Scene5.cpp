#include "Scene5.h"
#include <SDL.h> 
#include <SDL_image.h>
#include "VMath.h"
#include "Randomizer.h"
using namespace MATH;
using namespace std;

Scene5::Scene5(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Scene5 ERROR: Can´t create renderer ";
	}
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	cout << "Scene5 ACTIVATED" << endl;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	Randomizer r;
	r.rand(0.0f, 20.0f);

	menu = new Body(Vec3(0.0f, 15.0f, 0.0f));
	space = new Body(Vec3(5.0f, 15.0f, 0.0f));

	for (float x = 0.0f; x < 30.0f; x += 5.0f)
	{
		boulder.push_back(new Body(Vec3(r.rand(0.0f, 20.0f), r.rand(0.0f, 20.0f), 0.0f)));

	}

	for (int i = 0; i < boulder.size(); ++i)
	{
		boulder[i]->setVel(Vec3(r.rand(0.0f, 10.0f), 0.0f, 0.0f));
		boulder[i]->setAccel(Vec3(0.0f, -9.81f, 0.0f));
	}


}

Scene5::~Scene5() {
	for (int i = 0; i < boulder.size(); ++i)
	{
		delete boulder[i];
	
	}
	delete menu;
	delete space;
	if (renderer) SDL_DestroyRenderer(renderer);

}

bool Scene5::OnCreate() {
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


	image = IMG_Load("textures/menu.png");
	menuTexture = SDL_CreateTextureFromSurface(renderer, image);
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

	for (int i = 0; i < boulder.size(); ++i)
	{
		boulder[i]->setRadius(size.x / 2.0f);
	}
	return true;
}

void Scene5::OnDestroy() {

}

void Scene5::Update(const float deltaTime) {

	for(int i = 0; i < boulder.size(); ++i)
	{
		//Show off -> static cast
	boulder[i]->Update(deltaTime);
	}

	for(int i = 0; i < boulder.size() - 1; ++i)
	{
		for(int j = i+1 ; j < boulder.size() ; ++j)
		{
			float distance = VMath::distance(boulder[i]->getPos(), boulder[j]->getPos());
			//ASK SCOTT ABOUT THIS  
			if (distance <= boulder[i]->getRadius() + boulder[j]->getRadius())
			{
				//cout << "Collision" << endl;
				//velocity vector Boulder
				Vec3 v1 = boulder[i]->getVel();
				float m1 = boulder[i]->getmass();
				//velocity vector Boulder
				Vec3 v2 = boulder[j]->getVel();
				float m2 = boulder[j]->getmass();
				// coeficient of restitution a.k.a bounciness
				float e = 1.0f;

				Vec3 lineOfActtion = boulder[i]->getPos() - boulder[j]->getPos();
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

				boulder[i]->setVel(v1new);
				boulder[j]->setVel(v2new);
			}
			else {
				//cout << "nada" << endl;
			}
		}
	}


}

void Scene5::HandleEvent(const SDL_Event& sdlEvent)
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			cout << "- up" << endl;
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


void Scene5::Render()const {
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	for (int i = 0; i < boulder.size(); ++i)
	{
		screenCoords = projectionMatrix * boulder[i]->getPos();
		//Ask for the height of the texture -cliff
		SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
		//Assign the w and h of the image as it is
		square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
		square.y = (int)screenCoords.y;
		square.w = width;
		square.h = height;
		SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, boulder[i]->getAngle(), nullptr, SDL_FLIP_NONE);
	}
	//render manu image

	screenCoords = projectionMatrix * menu->getPos();
	//Ask for the height of the texture -cliff
	SDL_QueryTexture(menuTexture, nullptr, nullptr, &width, &height);
	//Assign the w and h of the image as it is
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, menuTexture, &square, &square,0.0f, nullptr, SDL_FLIP_NONE);
	
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
