#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

/********************************************************************************************************************/
/*												World Class Header													*/
/* The world is where the snake moves, it includes the boundaries to where the snake can go	and is responsible		*/
/* of respawning the applePosition																					*/
/********************************************************************************************************************/

class World {
public:
	//Constructor
	World(sf::Vector2u l_windSize);

	//Deconstructor
	~World();

	//Return the size of block
	int GetBlockSize();

	//Respawn the applePosition
	void RespawnApple();

	//Update
	void Update(Snake& l_player);

	//Render window
	void Render(sf::RenderWindow& l_window);
private:
	//Size of window
	sf::Vector2u windowSize;
	//Cooridnates of the applePosition
	sf::Vector2i applePosition;
	//Size of each block
	int blockSize;

	//Apple
	sf::CircleShape appleShape;
	//Array of the 4 boundaries of the game, each represneted as a rectangle
	sf::RectangleShape bounds[4];

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	sf::Texture appleTexture;
	sf::Sprite appleSprite;
};