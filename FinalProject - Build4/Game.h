#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "Textbox.h"

/*
----- Game Class Header -----
Game loop content includes processing input, updating the game world and the player and rendering
everything on the screen. This class will help to roganize and refractor all these processes.
The class holds an instance of Window class, Snake oject	and World object
*/
class Game {
public:
	//Default Constructor
	Game();
	//Deconstructor
	~Game();

	//Handle input of the game (later implementation)
	void HandleInput();

	//Update the game
	void Update();

	//Render the contents of the game
	void Render();

	//Get the window (reference)
	Window* GetWindow();

	//Get the elapsed time of clock
	sf::Time GetElapsed();

	//Restart clock
	void RestartClock();
private:
	//Instance of Window
	Window window;
	//Clock object
	sf::Clock clock;
	//Time object to hold elapsed time between iterations
	float elapsedTime;

	//World of the game
	World world;
	//Snake object
	Snake snake;
	//Textbox object
	Textbox textbox;

};