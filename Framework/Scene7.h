#ifndef SCENE7_H
#define SCENE7_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include <vector>
#include "randomizer.h"
using namespace std;
using namespace MATH;
class Scene7 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;
	vector<Body*> objects;
	Body* boulder;
	Body* flappy;
	double boulderAngle;
	SDL_Texture* cliffTexture;
	SDL_Texture* flappyTexture;
	Body* space;
	SDL_Surface* spaceImage;
	SDL_Texture* spaceTexture;
	Randomizer rnd;


public:
	Scene7(SDL_Window* sdlWindow);
	virtual ~Scene7();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

