#ifndef SCENE2_H
#define SCENE2_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Body* cliff;
	Body* flappy;
	SDL_Texture* cliffTexture;
	SDL_Texture* flappyTexture;


public:
	Scene2(SDL_Window* sdlWindow);
	virtual ~Scene2();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

