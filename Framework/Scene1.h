#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	Matrix4 projectionMatrix;
	Body* cliff;
	Body* flappy ;
	SDL_Texture* cliffTexture;
	SDL_Texture* flappyTexture;
	Body* space;
	SDL_Surface* spaceImage;
	SDL_Texture* spaceTexture;
public:
	Scene1(SDL_Window* sdlWindow);
	virtual ~Scene1();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

