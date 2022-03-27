#ifndef SCENE4_H
#define SCENE4_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene4 : public Scene {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Body* boulder;
	Body* boulder1;
	//Body* boulder[3];
	double boulderAngle;
	SDL_Texture* cliffTexture;
	SDL_Texture* flappyTexture;
	Body* space;
	SDL_Surface* spaceImage;
	SDL_Texture* spaceTexture;

public:
	Scene4(SDL_Window* sdlWindow);
	virtual ~Scene4();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render()const;
	virtual void HandleEvent(const SDL_Event& sdlEvent);

};

#endif

