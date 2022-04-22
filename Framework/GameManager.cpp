#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "Scene1.h"//GAME101 - Flappy falling ASSIGNMENT 1 COMPLETE
#include "Scene2.h"//Flappy at angle - Umer
#include "Scene3.h"//GAME101 - Boulder rolling ASSIGNMENT 2 COMPLETE
#include "Scene4.h"//Two boulders colliding
#include "Scene5.h"//GAME101 - Bunch of boulders colliding ASSIGNMENT 3 COMPLETE
#include "Scene6.h"//GAME101 - Umer's Gravity well but cool  
#include "Scene7.h"//Template - Random boulders colliding at will
#include "Scene8.h"//Boy running 
#include "Scene01.h"//spaceship
#include "Scene03.h"//collision
#include "Scene04.h"//collision

#include <iostream>

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}

GameManager::~GameManager() {

}

/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1500;
	const int SCREEN_HEIGHT = 560;
	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}
	//To change scenes
	currentScene = new Scene04(windowPtr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	SDL_Event sdlEvent;
	timer->Start();
	while (isRunning == true) {
		timer->UpdateFrameTicks();
		//Handle events on queue
		while (SDL_PollEvent(&sdlEvent) != 0) {
			//User requests quit (by clicking x at the top)
			if (sdlEvent.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (sdlEvent.type == SDL_KEYDOWN) {
				switch (sdlEvent.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;
				case SDL_SCANCODE_DELETE:
					isRunning = false;
					break;
				default:
					HandleEvents(sdlEvent);
					break;
				}
			}
			currentScene->HandleEvent(sdlEvent);

		}
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
	currentScene->OnDestroy();
	delete currentScene;
	return; /// all done, back to main()
}



void GameManager::OnDestroy() {
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene != nullptr) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
}

void GameManager::HandleEvents(const SDL_Event& sdlEvent) 
{
	switch (sdlEvent.key.keysym.scancode)
	{
		case SDL_SCANCODE_F1:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene01(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;
		case SDL_SCANCODE_F2:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene03(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;
		case SDL_SCANCODE_F3:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene04(windowPtr->GetSDL_Window());
			currentScene->OnCreate();
			break;

		case SDL_SCANCODE_F4:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene4(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			
			break;
		case SDL_SCANCODE_F5:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene5(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;
		case SDL_SCANCODE_F6:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene6(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;
		case SDL_SCANCODE_F7:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene7(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;
		;
		case SDL_SCANCODE_F8:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene8(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;

		case SDL_SCANCODE_M:
			currentScene->OnDestroy();
			delete currentScene;
			currentScene = new Scene5(windowPtr->GetSDL_Window());
			currentScene->OnCreate();

			break;

	}
}
