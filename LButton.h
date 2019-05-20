#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#ifndef __LBUTTON_H__
#define __LBUTTON_H__

//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);


public:
	enum LButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
		BUTTON_SPRITE_MOUSE_DOWN = 2,
		BUTTON_SPRITE_MOUSE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	;

	//Button constants
	const int BUTTON_WIDTH = 300;
	const int BUTTON_HEIGHT = 200;
	const int TOTAL_BUTTONS = 4;

	int posX, posY;


private:
	//Top left position
	SDL_Point mPosition;


};

#endif