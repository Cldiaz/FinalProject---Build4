#include "Textbox.h"

/*
----- Textbox Class Header -----
The Textbox class allows us to print a series of messages to the screen. When a new message is added, it is
added to the bottom of the older message as the older message moves up.
This textbox displays the foolowing messages for debugging purposes:
- When the player loses a life and how many lives he has
- At the beginning, the starting position of the apple
- The current score of the user
*/

/*
----- Default Constructor -----
Used to initialize Textbpx object with default
values. Call Setup method
*/
Textbox::Textbox() {
	Setup(5, 9, 200, sf::Vector2f(0, 0));
}

/*
----- Constructor -----
Used to initialize Textbox object. Call Setup method
@param numberOfLines  Number of visible lines
@param charSize	 Charter size
@param width  Width of the etre Texbox
@param screenPosition  Position where to draw it
*/
Textbox::Textbox(int numberOfLines, int charSize, int width, sf::Vector2f screenPosition) {
	//Call Setup method
	Setup(numberOfLines, charSize, width, screenPosition);
}

/*
----- Deconstructor -----
*/
Textbox::~Textbox() {
	//Call Clear method
	Clear();
}

/*
----- Setup Function -----
Create Textbox object.
@param numberOfLines Number of visible lines
@param charSize	 Charter size
@param width Width of the etre Texbox
@param screenPosition  Position where to draw it
*/
void Textbox::Setup(int numberOfLines, int charSize, int width, sf::Vector2f screenPosition) {
	visibleLines = numberOfLines;
	//Define an ofset used to space the text approximately and provide some padding from the top-left corner
	sf::Vector2f offset(2.0f, 2.0f);

	font.loadFromFile("arial.ttf");//Load font
	textContent.setFont(font);//Set the font
	textContent.setString("");//Set an empty string
	textContent.setCharacterSize(charSize);//Set the char size
	textContent.setColor(sf::Color::White);//Set the font color
	textContent.setPosition(screenPosition + offset);//Set the position with the offset
	rectangleBackdrop.setSize(sf::Vector2f(width, (numberOfLines * (charSize * 1.2f))));//Set the size of the backrop rectangle
	rectangleBackdrop.setFillColor(sf::Color(90, 90, 90, 90));//Set the fill color of the rectangle
	rectangleBackdrop.setPosition(screenPosition);//Set the position of the rectangle
}

/*
----- Add Function -----
Add message to textbox
@param message	Message to be addeed
*/
void Textbox::Add(std::string message) {
	messages.push_back(message);//Add message to vector
	if (messages.size() < 6) { return; }//If less than 6 "messages", return
	messages.erase(messages.begin());//If not, delete the first one
}

/*
----- Clear Function -----
Clear vector of messages
*/
void Textbox::Clear() { messages.clear(); }

/*
----- Render Function -----
Render texbox to window
@param window  Reference to the window
*/
void Textbox::Render(sf::RenderWindow& window) {
	std::string content;
	//Iterate throught vector and append all the messages to string
	for (auto &itr : messages) {
		content.append(itr + "\n");
	}

	if (content != "") {//Make sure we have messages
		textContent.setString(content);//Set the content to the textbox
		window.draw(rectangleBackdrop);//Draw the backdrop
		window.draw(textContent);//Draw the text
	}
}