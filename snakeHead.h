#pragma once

#include <SDL.h>
#include "macros.h"
#include <math.h>
#include <time.h>
#include "Rectangle.h"
#include "particle.h"
#include "LTexture.h"
#ifndef __SNAKEHEAD_H__
#define __SNAKEHEAD_H__

class snakeHead {
private:
	int highscore = 0;
	int xPos, yPos, xVel, yVel;
	bool spawnRects = false;
	int remSpawnFrames = 0;
	double angle = 0, renderAngle = 0;
	SDL_Point center;
	SDL_Renderer* Renderer = NULL;
	Rectangle food;
	SDL_Rect windowRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	
	
	static const int TOTAL_PARTICLES = 4000;
	Particle* particles[TOTAL_PARTICLES];

	int maxparticleframes = 200;

	LTexture* XabHead;
public:
	static const int HEAD_WIDTH = 56, HEAD_HEIGHT = 87;
	static const int MAX_VEL = 4;
	Rectangle Rect;
	Rectangle simRect;
	bool loser = false;
	bool updateScore = false;

private:
	void renderParticles();
	void checkCollisions();
	void randomPosition();
public:
	snakeHead();
	snakeHead(SDL_Renderer* oRenderer);
	~snakeHead();

	void handleEvent(SDL_Event* e);
	void move();
	void render();

	int getHighScore() { return highscore; }
};

#endif
