#pragma once
//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "LButton.h"
#include "snakeHead.h"
#include "menu.h"

#ifndef __LAPP_H__
#define __LAPP_H__
//-----------------------------------------------------------//
class App {
private:
	static App Instance;

	bool Running = true;
	bool updateScore = false;

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Surface* PrimarySurface = NULL;

	static const int WindowWidth = 1440;
	static const int WindowHeight = 800;

	snakeHead* player = nullptr;
	Menu* menu = nullptr;

	menuButton* score = nullptr;
	menuButton* scoreLabel = nullptr;
	SDL_Rect windowRect = { 0,0,WindowWidth,WindowHeight };
	//mouse replacement box
	Rectangle* laserpointer = nullptr;

private:
	App();

	// Capture SDL Events
	void OnEvent(SDL_Event* Event);

	// Initialize our SDL game / app
	bool Init();

	// Logic loop
	void Loop();

	// Render loop (draw)
	void Render();

	// Free up resources
	void Cleanup();

	bool Init_SDL_Convenience();


public:
	int Execute(int argc, char* argv[]);

	//bool LoadMedia();

public:
	static App* GetInstance();

	static int GetWindowWidth();
	static int GetWindowHeight();



};

#endif