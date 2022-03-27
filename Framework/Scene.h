#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"
class Scene {
public:
	//=0 means it's abstract and for it to behave polym -virtual
	//It's just to 'order' the methods
	virtual ~Scene() {};
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	//It prevents changes made by render
	virtual void Render() const = 0;
	virtual void HandleEvent(const SDL_Event& sdlEvent)=0;
};

#endif
