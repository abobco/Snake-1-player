#pragma once
#include "Rectangle.h"
#include <SDL.h>

class Particle
{
private:
	//Offsets
	int xPos, yPos;
	static const int  PARTICLE_WIDTH = 10, PARTICLE_HEIGHT = 10;
	SDL_Renderer* Renderer;
	 int frame = 0;
	 int maxframe;
public:
	//rendering rectangle
	Rectangle Rect;

public:
	//Initialize position and animation
	Particle(int oframe, int omaxframe, int x, int y, SDL_Renderer* oRenderer);

	//Shows the particle
	void render();

	//Checks if particle is dead
	bool isDead();

	int getFrame() { return frame; }
	void setFrame(int oframe) { frame = oframe; }
	void incFrame() { frame++; }

	void setMaxFrame(int omaxframe) { maxframe = omaxframe; }
};
