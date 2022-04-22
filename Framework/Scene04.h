#ifndef SCENE04_H
#define SCENE04_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "PhysicsObject.h"
#include "Vector.h"
#include "VMath.h"
#include "Physics.h"
#include <vector>
#include "Plane.h"
using namespace MATH;
class Scene04 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	PhysicsObject* staticSphere;
	PhysicsObject* crazySphereA;
	PhysicsObject* crazySphereB;
	PhysicsObject* crazySphereC;
	PhysicsObject* crazySphereD;

	Plane* plane;

	SDL_Texture* spheresTexture;

	float elapsedTime;

public:
	Scene04(SDL_Window* sdlWindow);
	virtual ~Scene04();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);


};

#endif

