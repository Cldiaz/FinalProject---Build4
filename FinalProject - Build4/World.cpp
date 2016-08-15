#include "World.h"

/*
----- World Class Functions -----
The world is where the snake moves, it includes the boundaries to where the snake can goand is responsible
of respawning the applePosition.
*/

/*
----- Constructor -----
Takes a vector of two unsigned integers as an
argument which represent the window size.
@param windSize  Size of the window
*/
World::World(sf::Vector2u windSize) {
	bgTexture.loadFromFile("black-bg.png");
	bgSprite.setTexture(bgTexture);
	blockSize = 20;//Define the size of block
	windowSize = windSize;//Assign the window size
	appleTexture.loadFromFile("apple.png");
	appleSprite.setTexture(appleTexture);
	RespawnApple();//Call RespawnApple() to respawn the applePosition

	appleShape.setFillColor(sf::Color::Red);//Set the color of the applePosition
	appleShape.setRadius(blockSize / 2);//Set the radius of the applePosition
	//Loop 4 times, number of boundaries
	for (int i = 0; i < 4; ++i) {
		bounds[i].setFillColor(sf::Color(150, 0, 0));//Set the color of rectangle

		//Determine if the i is even or odd, to know how big each "wall" has to be on a specific axis
		if (!((i + 1) % 2)) {//even
							 //Set the size of the rectangle to the size of the windows in x axis and height of the block size
			bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		}
		else {//odd
			  //Set the size of the rectangle to block size and heigt of thr size of the windows in the y axis
			bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));
		}
		//If it is the Top or the Left wall
		if (i < 2) {
			bounds[i].setPosition(0, 0);//Set the position at  0,0 (top-left corner of window)
		}
		//If it is the Bottom or Right wall
		else {
			bounds[i].setOrigin(bounds[i].getSize());//Set the origin to the its size, making in bottom right corner
			bounds[i].setPosition(sf::Vector2f(windowSize));//Set the position to size of the window, this places it all the way to the bottom right corner
		}
	}
}

/*
----- Deconstructor -----
*/
World::~World() {}

/*
----- GetBlockSize Function -----
@return blockSize  The block size
*/
int World::GetBlockSize() { return blockSize; }

/*
----- RespawnApple	Function -----
Responsible of respawning the applePosition
inside the boundaries.
*/
void World::RespawnApple() {
	//Get the maximum value in the x axis, size of the window in x divided by block size (number of spaces in grid) minus 2 (two block of boundaries)
	int maxX = (windowSize.x / blockSize) - 2;
	//Get the maximum value in the y axis
	int maxY = (windowSize.y / blockSize) - 2;
	//Generate and store the position where applePosition is going respawn
	applePosition = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	//Set the position of the applePosition to the coordinates we previously generated
	appleShape.setPosition(applePosition.x * blockSize, applePosition.y * blockSize);
	appleSprite.setPosition(applePosition.x * blockSize, applePosition.y * blockSize);
}

/*
----- Update Function -----
Check if snake position is the same as
applePosition position or if snake hit wall
@param player  Reference to the snake object
*/
void World::Update(Snake& player) {
	//If snake position is the same as the position of the applePosition
	if (player.GetPosition() == applePosition) {
		player.Extend();//Call Exted() to extend the snake
		player.IncreaseScore();//Call IncreaseScore() to increase the score of player
		RespawnApple();//Call RespawnApple() to respawn new applePosition
	}

	int gridSize_x = windowSize.x / blockSize;//Determine and store grid size on x axis
	int gridSize_y = windowSize.y / blockSize;//Determine and store grid size on y axis

											  //Check if snake position hit bounaries
	if (player.GetPosition().x <= 0 ||
		player.GetPosition().y <= 0 ||
		player.GetPosition().x >= gridSize_x - 1 ||
		player.GetPosition().y >= gridSize_y - 1)
	{
		player.Lose();//Call Lose() function of the snake to handle lost
	}
}

/*
----- Update Function -----
Render applePosition and boundaries in window
@param window  Reference to the window object
*/
void World::Render(sf::RenderWindow& window) {

	window.draw(bgSprite);
	//Draw the 4 walls
	for (int i = 0; i < 4; ++i) {
		window.draw(bounds[i]);
	}
	//Draw the applePosition
	window.draw(appleSprite);
}