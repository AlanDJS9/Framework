#ifndef SCENE8_H
#define SCENE8_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include <vector>
#include "randomizer.h"
using namespace std;
using namespace MATH;
class Scene8 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;
	vector<Body*> objects;
	Body* boulder;
	Body* boy;
	Body* menu;
	double boulderAngle;
	SDL_Surface* menuImage;
	SDL_Texture* cliffTexture;
	SDL_Texture* menuTexture;
	//Pass tecture to body
	SDL_Texture* boyTexture;
	Body* space;
	SDL_Surface* spaceImage;
	SDL_Texture* spaceTexture;
	Randomizer rnd;
	

public:
	Scene8(SDL_Window* sdlWindow);
	virtual ~Scene8();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);
	void HandleEvents(const SDL_Event& sdlEvent);

};

#endif

