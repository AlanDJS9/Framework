#ifndef SCENE5_H
#define SCENE5_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include <vector>
using namespace std;
using namespace MATH;
class Scene5 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Body* menu;
	Body* space;
	SDL_Surface* menuImage;
	SDL_Surface* spaceImage;
	vector<Body*> boulder;
	double boulderAngle;
	SDL_Texture* cliffTexture;
	SDL_Texture* menuTexture;
	SDL_Texture* spaceTexture;



public:
	Scene5(SDL_Window* sdlWindow);
	virtual ~Scene5();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

