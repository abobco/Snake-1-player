#include "particle.h"

//Initialize position and animation
Particle::Particle(int oframe, int omaxframe, int x, int y, SDL_Renderer* oRenderer)
{
	frame = oframe;
	maxframe = omaxframe;
	xPos = x + 20;
	yPos = y + 40;

	Rect = Rectangle(xPos, yPos, PARTICLE_WIDTH, PARTICLE_HEIGHT, 100, 0, 200);
	Renderer = oRenderer;
}
//Shows the particle
void Particle::render()
{
	if (!isDead())
		Rect.render(Renderer);
}


//Checks if particle is dead
bool Particle::isDead()
{
	return frame > maxframe;
}