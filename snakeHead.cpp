#include "snakeHead.h"


snakeHead::snakeHead()
{
	//Initialize the offsets
	xPos = 100;
	yPos = 100;
	center = { xPos + 5, yPos + 5 };

	//Initialize the velocity
	xVel = 0;
	yVel = 0;
}

snakeHead::snakeHead(SDL_Renderer* oRenderer)
{
	//Initialize the offsets
	xPos = 100;
	yPos = 100;
	center = { xPos + HEAD_WIDTH / 2 , yPos + HEAD_HEIGHT / 2 };
	//Initialize the velocity
	xVel = 0;
	yVel = 0;

	Renderer = oRenderer;

	Rect = Rectangle(xPos, yPos, HEAD_WIDTH, HEAD_HEIGHT, 100, 0, 200);
	simRect = Rectangle(xPos, yPos, 20, 20);
	food = Rectangle(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, 20, 20, 190, 120, 0);

	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		if (i < maxparticleframes)
			particles[i] = new Particle(i, maxparticleframes, xPos, yPos, oRenderer);
		else
			particles[i] = nullptr;
	}

	XabHead = new LTexture(Renderer);
	if (!XabHead->loadFromFile("XabNab.png", Renderer))
		printf("Failed to load image!\n");

	

}

snakeHead::~snakeHead()
{
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		delete particles[i];
	}
}

void snakeHead::handleEvent(SDL_Event* e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Point mousePos{ x, y };

	/*if (SDL_PointInRect(&mousePos, &Rect.getRect()))
		xVel = yVel = 0;
	else
	{*/
		int deltaX = x - xPos, deltaY = yPos - y;

		angle = atan(double(deltaY) / deltaX);
		

		if (deltaY * deltaX < 0)
			angle *= -1;


		if (x > xPos)
			xVel = MAX_VEL * cos(angle);
		else
			xVel = -MAX_VEL * cos(angle);
		if (y > yPos)
			yVel = MAX_VEL * sin(angle);
		else
			yVel = -MAX_VEL * sin(angle);
	/*}*/
}

void snakeHead::move()
{
	//Move the point left or right
	xPos += xVel;
	//Move the point up or down
	yPos += yVel;

	Rect.setPosition(xPos, yPos);
	simRect.setPosition(xPos, yPos);
	center = { xPos + 5 , yPos + 5 };

	checkCollisions();

	int x, y;
	SDL_GetMouseState(&x, &y);

	if ( abs(y - yPos) > 20 && abs(x - xPos) > 20)
		renderAngle = atan((y - yPos) / double(x - xPos)) * 180/M_PI;

	/*if (x > xPos)
	{
		if (y > yPos) {
			renderAngle = atan((y - yPos) / double(x - xPos)) * 180 / M_PI;
		}
		else {
			renderAngle = atan((yPos - y) / double(x - xPos)) * 180 / M_PI + 270;
		}
	}
	else
	{
		
		if (y > yPos) {
			renderAngle = atan((y - yPos) / double(xPos - x)) * 180 / M_PI + 90;
		}	
		else {
			renderAngle = atan((yPos - y) / double(xPos - x)) * 180 / M_PI + 180;
		}		
	}*/

	for (int i = 0; i < maxparticleframes; i++)
	{
		if (particles[i] != nullptr)
			particles[i]->incFrame();
	}

}
void snakeHead::checkCollisions()
{
//WINDOW EDGE COLLISIONS
		//If the head went too far to the left or right
	if ((xPos < 0) || (xPos + HEAD_WIDTH > WINDOW_WIDTH))
	{
		//Move back
		loser = true;
	}
	//If the head went too far up or down
	if ((yPos < 0) || (yPos + HEAD_HEIGHT > WINDOW_HEIGHT))
	{
		//Move back
		loser = true;
	}

//RECT ON RECT COLLISIONS
		//check for tail collisions
	for (int i = 0; i < maxparticleframes; i++)
	{
		if (particles[i] != nullptr)
		{
			if (particles[i]->getFrame() > 30)
			{
				if (SDL_HasIntersection(&simRect.getRect(), &particles[i]->Rect.getRect()))
				{
					loser = true;
				}
			}
		}
	}
	//check for food collision
	if (SDL_HasIntersection(&Rect.getRect(), &food.getRect()))
	{
		randomPosition();
		highscore++;
		updateScore = true;
		if (!spawnRects)
		{
			if (maxparticleframes < TOTAL_PARTICLES)
			{
				spawnRects = true;

				for (int i = 0; i < maxparticleframes; i++)
				{
					if (particles[i] != nullptr)
						particles[i]->setMaxFrame(maxparticleframes + 100);
				}

				maxparticleframes += 100;
				remSpawnFrames += 100;

			}
		}
	}
}


void snakeHead::render()
{
	//Rect.render(Renderer);
	//SDL_RenderCopyEx(Renderer, XabHead->getTexture(), NULL, &Rect.getRect(), angle, &center, SDL_FLIP_NONE);

	food.render(Renderer);
	renderParticles();
	XabHead->render(xPos, yPos, NULL, renderAngle);
}

void snakeHead::renderParticles()
{

	//Go through particles
	if (!spawnRects)
	{
		for (int i = 0; i < maxparticleframes; ++i)
		{
			if (particles[i] != nullptr)
			{
				//Delete and replace dead particles
				if (particles[i]->isDead())
				{
					delete particles[i];
					particles[i] = new Particle(0, maxparticleframes, xPos, yPos, Renderer);
				}
				particles[i]->render();
			}
		}
	}
	else if (spawnRects)
	{
		for (int i = 0; i < maxparticleframes; ++i)
		{
			if (particles[i] != nullptr)
			{
				particles[i]->render();
			}
		}

		particles[maxparticleframes - remSpawnFrames] = new Particle(0, maxparticleframes, xPos, yPos, Renderer);
		particles[maxparticleframes - remSpawnFrames]->render();
		--remSpawnFrames;
		if (remSpawnFrames <= 0)
			spawnRects = false;
		
	}
}

//RNG
void snakeHead::randomPosition()
{
	//srand(time(NULL));
	SDL_RenderSetViewport(Renderer, &windowRect);
	food.setPosition(( rand()%600 )  + 200, (rand()%500) + 150);
}