#include "menu.h"

Menu::Menu()
{

	Rectangle titleRect = Rectangle(WINDOW_WIDTH / 2, 0, 300, 100);
	Rectangle startRect = Rectangle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300, 100);
	Rectangle scoreRect = Rectangle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150, 300, 100);
	Rectangle scoreLabelRect = Rectangle(WINDOW_WIDTH / 2 - 310, WINDOW_HEIGHT / 2 - 150, 300, 100);
	startButton = new menuButton(startRect, "Play Again", Renderer);
	scoreDisplay = new menuButton(scoreRect, "0", Renderer);
	scoreDisplay->loadText(Renderer);
	scoreLabel = new menuButton(scoreLabelRect, "Score:", Renderer);
	
}

Menu::Menu(SDL_Renderer* oRenderer)
{
	Renderer = oRenderer;

	Rectangle titleRect = Rectangle(WINDOW_WIDTH / 2 - 400, 10, 800, 100);
	Rectangle startRect = Rectangle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300, 100);
	Rectangle scoreRect = Rectangle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150, 300, 100);
	Rectangle scoreLabelRect = Rectangle(WINDOW_WIDTH / 2 - 310, WINDOW_HEIGHT / 2 - 150, 300, 100);
	startButton = new menuButton(startRect, "Play Again", Renderer);
	scoreDisplay = new menuButton(scoreRect, "0", Renderer);
	scoreDisplay->loadText(Renderer);
	scoreLabel = new menuButton(scoreLabelRect, "Score:", Renderer);
	title = new menuButton(titleRect, "SNAKE SNAKE OoOH ITS A SNAKE", Renderer);
}



Menu::~Menu()
{
	delete startButton;
	startButton = nullptr;
	delete scoreDisplay;
	scoreDisplay = nullptr;
}

void Menu::handleEvent(SDL_Event * e)
{
	startButton->handleEvent(e);
	if (startButton->pressed)
	{
		exit = true;
		startButton->pressed = false;
	}
}

void Menu::render()
{
	startButton->render(Renderer);
	scoreDisplay->render(Renderer);
	scoreLabel->render(Renderer);
	title->render(Renderer);
}

void Menu::setHighScore(int highscore)
{
	scoreDisplay->changeText(std::to_string(highscore));
	scoreDisplay->loadText(Renderer);
}
