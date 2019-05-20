#include "LApp.h"


//Game window
App App::Instance;
//I think this has to be here for Instance. Could be used to initialize complex objects which contain no SDL components.
App::App() {}

// global app loop:
//		This can be treated like the main() function of the app. 
//		This function calls every function in the game
int App::Execute(int argc, char* argv[]) {
	if (!Init()) return 0;

	SDL_Event Event;

	while (Running) {
		while (SDL_PollEvent(&Event) != 0) {
			if (Event.type == SDL_QUIT) Running = false;
			OnEvent(&Event);
		}

		Loop();

		Render();

		SDL_Delay(1); // Breath
	}

	Cleanup();

	return 1;
}

//global event handler. Handles user input
void App::OnEvent(SDL_Event* Event) {

	//if not in menu
	if (menu->exit)
	{
		if (player != nullptr)
			player->handleEvent(Event);	// player gets the event
	}
	else
	{
		menu->handleEvent(Event);	//else menu gets the event
		if (menu->exit)	//set game conditions if exiting menu
		{
			player = new snakeHead(Renderer);	
			updateScore = true;
			SDL_RenderSetViewport(Renderer, &windowRect);
		}
	}
}

//initialization
//		This can be treated as a constructor for the app. 
//		It is important to initialize all pure SDL objects with Init_SDL_Convenience() before initializing objects which contain SDL objects as components
bool App::Init() {
	bool success = true;

	if (!Init_SDL_Convenience())
	{
		success = false;
	}
	else
	{
		//initialize all Bob made objects AFTER SDL has been successfully initialized
		player = new snakeHead(Renderer);
		menu = new Menu(Renderer);
		Rectangle ScoreRect = Rectangle(WINDOW_WIDTH / 2 - 100, 0, 60, 30);
		Rectangle ScoreLabelRect = Rectangle(WINDOW_WIDTH / 2 - 300, 0, 200, 30);
		score = new menuButton(ScoreRect, "0", Renderer);
		score->loadText(Renderer);
		scoreLabel = new menuButton(ScoreLabelRect, "Score:", Renderer);
		scoreLabel->loadText(Renderer);
		SDL_ShowCursor(SDL_DISABLE);
		laserpointer = new Rectangle(0, 0, 10, 10, 250, 0, 0);
	}
	return success;
}
//		Calls all SDL owned init functions
bool App::Init_SDL_Convenience()	
{
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		Window = SDL_CreateWindow("XabNab Level Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

//game logic loop
void App::Loop() {
	if (menu->exit)
	{
		if (player != nullptr)
		{
			player->move();

			if (player->updateScore)
			{
				updateScore = true;
				player->updateScore = false;
			}
			if (player->loser)
			{
				//delete player;
				//player = new snakeHead(Renderer);
				menu->setHighScore(player->getHighScore());
				player = nullptr;
				menu->exit = false;
				
			}
		}
	}
}

//image rendering
void App::Render() {

	SDL_SetRenderDrawColor(Renderer, 72, 72, 72, 0xFF);
	SDL_RenderClear(Renderer);
	SDL_RenderSetViewport(Renderer, &windowRect);
	if (menu->exit)
	{
		if (player != nullptr)
			player->render();
		if (updateScore)
		{
			score->changeText(std::to_string(player->getHighScore()));
			score->loadText(Renderer);
			updateScore = false;
		}
		if (score != nullptr)
			score->render(Renderer);
		if (scoreLabel != nullptr)
			scoreLabel->render(Renderer);
	}
	else
	menu->render();

	//mouse pointer replacement
	int x, y;
	SDL_GetMouseState(&x, &y);
	laserpointer->setPosition(x, y);
	laserpointer->render(Renderer);

	SDL_RenderPresent(Renderer);

}

//memory deallocation
void App::Cleanup() {
	if (Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if (Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	delete player;
	delete menu;

	SDL_Quit();
}

//getters
App* App::GetInstance() { return &App::Instance; }
int App::GetWindowWidth() { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }
