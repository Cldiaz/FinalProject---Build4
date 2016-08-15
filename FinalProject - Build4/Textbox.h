#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//Define an alias for the vector of MessageContainer, list of messages to print
using MessageContainer = std::vector<std::string>;

/*
----- Textbox Class Header -----
The Textbox class allows us to print a series of messages to the screen. When a new message is added, it is
added to the bottom of the older message as the older message moves up.
This textbox displays the foolowing messages for debugging purposes:
- When the player loses a life and how many lives he has
- At the beginning, the starting position of the apple
- The current score of the user
*/
class Textbox {
public:
	//Constructors
	Textbox();
	Textbox(int numLines, int charSize, int width, sf::Vector2f screenPosition);

	//Deconstructor
	~Textbox();

	//Setup the Textbox
	void Setup(int visibleLines, int charSize, int width, sf::Vector2f screenPosition);

	//Add message to textbox
	void Add(std::string message);

	//Clear the messages
	void Clear();

	//Render the messages
	void Render(sf::RenderWindow& window);
private:
	//Vector of messages
	MessageContainer messages;
	//Number of visible lines
	int visibleLines;
	//Rectangle shape
	sf::RectangleShape rectangleBackdrop;
	//Font
	sf::Font font;
	//Text object
	sf::Text textContent;
};