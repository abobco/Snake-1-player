#pragma once
#include <SDL.h>
#include "menuButton.h"

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

class Menu
{
private:
	menuButton* startButton = nullptr;
	menuButton* scoreDisplay = nullptr;
	menuButton* scoreLabel = nullptr;
	menuButton* title = nullptr;
	SDL_Renderer* Renderer = NULL;
public:
	bool exit = false;
public:
	Menu();
	Menu(SDL_Renderer* oRenderer);
	~Menu();
	void handleEvent(SDL_Event* e);

	void render();

	void setHighScore(int highscore);
};
#endif