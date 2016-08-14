#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
/********************************************************************************************************************/
/*												Window Class Header													*/
/* Since every game needs to have a window, is useful to have a class.												*/
/* Methods needed include being able to create, destroy, process events, draw,										*/
/* clear the screen and update itself to show anything drawn after the screen was cleared							*/
/* It's also usefull to keep track whether the window is being closed and if it's in full-screen mode.				*/
/********************************************************************************************************************/
class Window {
public:
	//Default constructor
	Window();

	//Constructor
	Window(const std::string& title, const sf::Vector2u& size);

	//Deconstructor
	~Window();

	//Clear window
	void BeginDraw();

	//Display changes
	void EndDraw();

	//Update the window content
	void Update();

	//Check if window is closed
	bool IsDone();

	//Check the status of window fullscreen or default
	bool IsFullscreen();

	sf::RenderWindow* GetRenderWindow();

	//Get the size of the window
	sf::Vector2u GetWindowSize();

	//Toggle fullscreen
	void ToggleFullscreen();

	//Draw to the window
	void Draw(sf::Drawable& l_drawable);
private:
	//Setup the window
	void Setup(const std::string title, const sf::Vector2u& size);

	//Create window
	void Create();

	//Destroy the window
	void Destroy();

	//Game window
	sf::RenderWindow window;
	//Size of the window
	sf::Vector2u windowSize;
	//Title of the windoow
	std::string windowTitle;
	//Closed/Open boolean
	bool isDone;
	//Fullscreen toggle boolean
	bool isFullscreen;
};