#pragma once
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include <vector>

/****************************************************/
/* SnakeSegment Structure							*/
/* Represents a segment of the snake body			*/
/* Contains a single member, an integer vector		*/
/* which represents the position of the segment		*/
/* on the grid.										*/
/****************************************************/
struct SnakeSegment {
	//Structure constructor, set the position through an initializer list
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;//integer vector to store the position
};

//Define an alias for the vector of SnakeSegments
using SnakeContainer = std::vector<SnakeSegment>;

//Enumeration defining the possible directions of the snake, also one to indicate is not moving
enum class Direction { None, Up, Down, Left, Right };

/********************************************************************************************************************/
/*												Snake Class Functions												*/
/* The Snake class contains the direction towards it is moving, the number of lives it has, keep track of the score	*/
/* after eating an applePosition, the speed, wheter the snake has lost (hitting the wall) or not,					*/
/* and the physical shape which is a rectangle that represents every segment of the snake							*/
/********************************************************************************************************************/
class Snake {
public:
	//Constructor
	Snake(int l_blockSize, Textbox* log);

	//Deconstructor
	~Snake();

	//Set the direction of the snake
	void SetDirection(Direction l_dir);

	//Return the direction where the snake is going
	Direction GetDirection();

	//Return the speed of the snake
	int GetSpeed();

	//Return the position of th snake
	sf::Vector2i GetPosition();

	//Return the number of lives the snake has
	int GetLives();

	//Return the score of the snake
	int GetScore();

	//Increment the score
	void IncreaseScore();

	//Return if the snake has lost
	bool HasLost();

	//Handle losing
	void Lose();

	//Toggle the lost variabe
	void ToggleLost();

	Direction GetPhysicalDirection();

	//Grow the snake, after eating applePosition
	void Extend();

	//Reset snake to the starting position
	void Reset();

	//Moveme the sanke
	void Move();

	//Update method, fixed time-step
	void Tick();

	//Cut the snake
	void Cut(int segments);

	//Render window
	void Render(sf::RenderWindow& window);

private:
	//Check collisions
	void CheckCollision();

	// Segment vector, the snake
	SnakeContainer snakeBody;
	int sizeBlock; // Size of the graphics.
				   //Direction toward the snake is moving
	Direction direction;
	//Speed of the snake
	int speed;
	//Lives of the snake
	int lives;
	//Score of the snake
	int score;
	//Has the snake lost or not
	bool lost;
	//Shape used in rendering, represents every segment of the snake
	sf::RectangleShape bodyRectangle;
	//Textbox object
	Textbox* logTextbox;

	//Textures for the diferent directions of the snake head
	sf::Texture headTextureRight;
	sf::Texture headTextureUp;
	sf::Texture headTextureDown;
	sf::Texture headTextureLeft;
	//Texture for the snake body
	sf::Texture bodyTexture;
	//Sprite for body and head
	sf::Sprite bodySprite;
	sf::Sprite headSprite;
};