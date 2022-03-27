#ifndef SCENE6_H
#define SCENE6_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include <vector>
using namespace std;
using namespace MATH;
#include "randomizer.h"

class Scene6 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;
	vector<Body*> objects;

	Body *star1;
	Body *star2;
	Body *planet;
	double boulderAngle;
	SDL_Texture *cliffTexture;
	SDL_Texture *shipTexture;
	SDL_Texture* marsTexture;
	Body* space;
	SDL_Surface* spaceImage;
	SDL_Texture* spaceTexture;
	Randomizer rnd;

public:
	Scene6(SDL_Window* sdlWindow);
	virtual ~Scene6();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

