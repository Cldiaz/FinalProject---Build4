#include "Window.h"
/********************************************************************************************************************/
/*												Window Class Functions												*/
/* Since every game needs to have a window, is useful to have a class.												*/
/* Functions needed include being able to create, destroy, process events, draw,									*/
/* clear the screen and update itself to show anything drawn after the screen was cleared							*/
/* It's also usefull to keep track whether the window is being closed and if it's in full-screen mode.				*/
/* Additional methods would include a way to toggle full screen.													*/
/********************************************************************************************************************/

/****************************************************/
/* Default Constructor								*/
/****************************************************/
Window::Window() {
	//Call Setup function
	Setup("Window", sf::Vector2u(640, 480));
}

/****************************************************/
/* Constructor										*/
/* @param title  Title of the window				*/
/* @param size 	 Size of the window					*/
/****************************************************/
Window::Window(const std::string& title, const sf::Vector2u& size) {
	//Call Setup function
	Setup(title, size);
}

/****************************************************/
/* Deconstructor									*/
/****************************************************/
Window::~Window() {
	//Call Destroy function
	Destroy();
}

/****************************************************/
/* Setup Function									*/
/* Intitialize Window class properties				*/
/* @param title  Title of the window				*/
/* @param size 	 Size of the window					*/
/****************************************************/
void Window::Setup(const std::string title, const sf::Vector2u& size) {
	windowTitle = title;//Assign the title of the window
	windowSize = size;//Assign the size of the window
	isFullscreen = false;//Initialize isFullscreen to false
	isDone = false;//Initialize isDone to false (window is open)
	Create();//Call Create function
}

/****************************************************/
/* Create Function									*/
/* Create a window, assign style to window			*/
/****************************************************/
void Window::Create() {
	//sf::Uint32 to hold the current style of the window
	auto style = (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	//Create window with the size (sf::ViewMode), title, and style (fullscreen or default)
	window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
}

/****************************************************/
/* Destroy Function									*/
/* Close the window									*/
/****************************************************/
void Window::Destroy() {
	window.close();
}

/****************************************************/
/* BeginDraw Function								*/
/* Clear the window before starting drawing			*/
/****************************************************/
void Window::BeginDraw() {
	window.clear(sf::Color::Black);
}

/****************************************************/
/* EndDraw Function									*/
/* Display the window now that we have draw			*/
/****************************************************/
void Window::EndDraw() {
	/*bgTexture.loadFromFile("bg.png");
	bgSprite.setTexture(bgTexture);
	window.draw(bgSprite);*/
	window.display();
}

/****************************************************/
/* IsDone Function									*/
/* Return if the window has been closed				*/
/****************************************************/
bool Window::IsDone() {
	return isDone;
}

/****************************************************/
/* IsFullscreen Function							*/
/* Return if the window is fullscreen				*/
/****************************************************/
bool Window::IsFullscreen() {
	return isFullscreen;
}

sf::RenderWindow* Window::GetRenderWindow() { return &window; }

/****************************************************/
/* GetWindowSize Function							*/
/* Return the window size							*/
/* @return Size of window							*/
/****************************************************/
sf::Vector2u Window::GetWindowSize() {
	return windowSize;
}

/****************************************************/
/* ToggleFullscreen Function						*/
/* Toggle fullscreen option of the window			*/
/****************************************************/
void Window::ToggleFullscreen() {
	//Toggle isFullscreen boolean
	isFullscreen = !isFullscreen;
	//Call Destroy() to close/destroy the current window
	Destroy();
	//Call Create() to re-create a new window with toggle applied
	Create();
}

/****************************************************/
/* Update Function									*/
/* Handle events of the window, for now, check if	*/
/* close button has been clicked or					*/
/* F5 has been pressed								*/
/****************************************************/
void Window::Update() {
	sf::Event event;
	//Lopp to check any events on our windows
	while (window.pollEvent(event)) {
		//Check if the closing button was clicked
		if (event.type == sf::Event::Closed) {
			isDone = true; //Flip boolean flag to indicate is closed
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { isDone = true; }
		//Check for key F5 pressed event 
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
			//Call ToggleFullscreen() to switch
			ToggleFullscreen();
		}
	}
}