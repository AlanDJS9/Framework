#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	Body* balloon1;
	Body* balloon2;
	Body* menu;
	SDL_Surface* ballImage;
	SDL_Surface* menuImage;
	Body* space;
	SDL_Surface* spaceImage;

	SDL_Renderer* renderer;
	SDL_Texture* menuTexture;


	
public:
	Scene0(SDL_Window* sdlWindow);
	virtual ~Scene0();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render() const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

