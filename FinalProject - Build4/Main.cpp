#include "Game.h"

/*
----- Snake Game - Final Project C++ -----
August 15, 2016
Cindy Diaz #200305923
This is a simple snake game, the goal is to grab the apple to add to your score. The player loses the game
if the snake hits the boundaries or runs out of lives.
Player starts with three lives and loses a life every time the snake head intersects the body.
*/
void main(int argc, void** argv[]) {
	//Game object
	Game game;
	//Loop until player closes the game
	while (!game.GetWindow()->IsDone()) {
		//Handle any input of the player
		game.HandleInput();
		//Update game
		game.Update();
		//Render game
		game.Render();
		//Restart clock
		game.RestartClock();
	}
}