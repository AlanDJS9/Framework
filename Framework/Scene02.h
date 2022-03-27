#ifndef SCENE02_H
#define SCENE02_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "PhysicsObject.h"
#include "Vector.h"
#include "VMath.h"
#include "Physics.h"
#include <vector>

using namespace MATH;
class Scene02 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	PhysicsObject* spaceShip;
	SDL_Texture* spaceShipTexture;
	
	float elapsedTime;

public:
	Scene02(SDL_Window* sdlWindow);
	virtual ~Scene02();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);
	
	//Array to store the data to print it out
	vector<float> timeArray;
	vector<float> AngAccelArray;
	vector<float> AngVelArray;
	vector<float> AngleArray;
	vector<float> ForceXArray;
	vector<float> ForceYArray;
	vector<float> AccelXArray;
	vector<float> AccelYArray;
	vector<float> VelXArray;
	vector<float> VelYArray;
	vector<float> PosXArray;
	vector<float> PosYArray;


};

#endif

