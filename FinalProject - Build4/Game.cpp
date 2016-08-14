#include "Game.h"

/********************************************************************************************************************/
/*												Game Class Functions												*/
/* Game loop content includes processing input, updating the game world and the player and rendering				*/
/* everything on the screen. This class will help to roganize and refractor all these processes.					*/
/* The class holds an instance of Window class, Snake oject	and World object										*/
/********************************************************************************************************************/

/****************************************************/
/* Default Constructor								*/
/* Setup the window and graphics.					*/
/* Setting up class members							*/
/* NOTE: Use of initialization list in constructor	*/
/* is needed to	initialize the Window object,		*/
/* snake object, and world object.					*/
/****************************************************/
Game::Game() : window("Snake Game", sf::Vector2u(800, 600)),
snake(world.GetBlockSize(), &textbox),
world(sf::Vector2u(800, 600))
{
	clock.restart();
	//Seed the random number generator
	srand(time(nullptr));
	//Set up the Texbox
	textbox.Setup(5, 14, 350, sf::Vector2f(225, 0));
	elapsedTime = 0.0f;

	textbox.Add("Seeded random number generator with: " + std::to_string(time(nullptr)));
}

/****************************************************/
/* Deconstructor									*/
/****************************************************/
Game::~Game() {}

/****************************************************/
/* GetElapsed Function								*/
/* Return the elapsed time since the last instance	*/
/* of the clock being restarted						*/
/* or since its creation							*/
/****************************************************/
sf::Time Game::GetElapsed() {
	return clock.getElapsedTime();
}

/****************************************************/
/* RestartClock Function							*/
/****************************************************/
void Game::RestartClock() {
	elapsedTime += clock.restart().asSeconds();
}

Window* Game::GetWindow() {
	return &window;
}

/****************************************************/
/* HandleInput Function								*/
/* Handle input of the player to change				*/
/* direction of snake								*/
/****************************************************/
void Game::HandleInput() {
	// Input handling for the arrow keys pressed, also check the player does not try to go opposite direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& snake.GetPhysicalDirection() != Direction::Down) {
		snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& snake.GetPhysicalDirection() != Direction::Up) {
		snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& snake.GetPhysicalDirection() != Direction::Right) {
		snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& snake.GetPhysicalDirection() != Direction::Left) {
		snake.SetDirection(Direction::Right);
	}
}
/****************************************************/
/* Update Function									*/
/****************************************************/
void Game::Update() {
	window.Update();
	float timestep = 1.0f / snake.GetSpeed();//Fixed time-step with the speed of the snake in order to update the apporpiate amount of times per second
	if (elapsedTime >= timestep) {
		snake.Tick();//Call Tick() from Snake class to move snake
		world.Update(snake);//Call Update() from World class to handle if snake eats applePosition or hit wall
		elapsedTime -= timestep;//decreased time elapsed
								//Check if after all this the player has lost
		if (snake.HasLost()) {
			textbox.Add("GAME OVER! Score: "
				+ std::to_string((long long)snake.GetScore()));
			snake.Reset();
		}
	}
}

/****************************************************/
/* Render Function									*/
/* Draw world and snake in our window				*/
/****************************************************/
void Game::Render() {
	window.BeginDraw();//Clear window	
	world.Render(*window.GetRenderWindow());//Pass the reference of the window to the World class to draw its content
	snake.Render(*window.GetRenderWindow());//Pass the reference of the window to the Snake class to draw its content
	textbox.Render(*window.GetRenderWindow());//Pass the reference of the window to the Textbox class to draw its content
	window.EndDraw();//Display output
}