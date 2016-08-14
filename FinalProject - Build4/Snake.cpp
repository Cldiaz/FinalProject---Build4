#include "Snake.h"
/********************************************************************************************************************/
/*												Snake Class Functions												*/
/* The Snake class contains the direction towards it is moving, the number of lives it has, keep track of the score	*/
/* after eating an applePosition, the speed, wheter the snake has lost (hitting the wall) or not, and the			*/
/* physical shape which is a rectangle that represents evry segment of the snake.									*/
/********************************************************************************************************************/

/****************************************************/
/* Constructor										*/
/* Takes an integer as an argumetn which represents	*/
/* the size of our graphics.						*/
/* 	@param blockSize  Size of block					*/
/****************************************************/
Snake::Snake(int blockSize, Textbox* log) {
	logTextbox = log;
	//Store the size of block
	sizeBlock = blockSize;
	//Set the size of the rectange, substract one to make the snake segment appear visually slightly separated
	bodyRectangle.setSize(sf::Vector2f(sizeBlock - 1, sizeBlock - 1));
	headTextureDown.loadFromFile("head-down.png");
	headTextureUp.loadFromFile("head-up.png");
	headTextureLeft.loadFromFile("head-left.png");
	headTextureRight.loadFromFile("head-right.png");
	bodyTexture.loadFromFile("body.png");
	bodySprite.setTexture(bodyTexture);
	headSprite.setTexture(headTextureDown);
	//Call Reset() which moves the snake to its starting position
	Reset();
}

/****************************************************/
/* Deconstructor									*/
/****************************************************/
Snake::~Snake() {}

/****************************************************/
/* SetDirection Function							*/
/* Set the direction to which the snake should move	*/
/* @param l_dir Direction snake should move next.	*/
/****************************************************/
void Snake::SetDirection(Direction l_dir) {
	//Set the direction memeber to the direction user selected
	direction = l_dir;
}

/****************************************************/
/* GetDirection Function							*/
/* Return the direction the snake is moving.		*/
/****************************************************/
Direction Snake::GetDirection() {
	return direction;
}

/****************************************************/
/* GetSpeed Function								*/
/* Return the speed the snake at which				*/
/* the snake is moving.								*/
/****************************************************/
int Snake::GetSpeed() {
	return speed;
}

/****************************************************/
/* GetPosition Function								*/
/* Return the position of the snake (the head)	.	*/
/****************************************************/
sf::Vector2i Snake::GetPosition() {
	return (!snakeBody.empty() ? snakeBody.front().position : sf::Vector2i(1, 1));
}

/****************************************************/
/* GetLives Function								*/
/* Return the lives the snake has.					*/
/****************************************************/
int Snake::GetLives() {
	return lives;
}

/****************************************************/
/* GetScore Function								*/
/* Return the score the snake has.					*/
/****************************************************/
int Snake::GetScore() {
	return score;
}

/****************************************************/
/* IncreaseScore Function							*/
/* Increase the score if snake eats an applePosition*/
/****************************************************/
void Snake::IncreaseScore() {
	logTextbox->Add("You ate an apple. Score: " + std::to_string((long long)score));
	score += 10;
}

/****************************************************/
/* HasLost Function									*/
/* Return the status of the snake, wheter it lost	*/
/* or not.											*/
/****************************************************/
bool Snake::HasLost() {
	return lost;
}

/****************************************************/
/* Lose Function									*/
/* Assignt to true the lost variable.				*/
/****************************************************/
void Snake::Lose() {
	lost = true;
}

/****************************************************/
/* ToggleLost Function								*/
/* Toggle to the lost variable.						*/
/****************************************************/
void Snake::ToggleLost() {
	lost = !lost;
}

/****************************************************/
/* GetPhysicalDirection Function					*/
/* Get the physical direction of the snake			*/
/****************************************************/
Direction Snake::GetPhysicalDirection() {
	if (snakeBody.size() <= 1) {
		return Direction::None;
	}

	SnakeSegment& head = snakeBody[0];
	SnakeSegment& neck = snakeBody[1];

	if (head.position.x == neck.position.x) {
		return (head.position.y > neck.position.y
			? Direction::Down : Direction::Up);
	}
	else if (head.position.y == neck.position.y) {
		return (head.position.x > neck.position.x
			? Direction::Right : Direction::Left);
	}

	return Direction::None;
}

/****************************************************/
/* Extend Function									*/
/* Handles the event when the snake eats an apple	*/
/* and the snake body needs to be extended			*/
/****************************************************/
void Snake::Extend() {
	if (snakeBody.empty()) { return; }//If  the sanke body is empty, exit
									  //Reference to the last segment of the snake body, referred in this case as tail_head 
	SnakeSegment& tail_head = snakeBody[snakeBody.size() - 1];

	//If the length of the snake is greater than just the head
	if (snakeBody.size() > 1) {
		//Reference to the next to the last element, reffered in this case as tail_bone, used to determine where to place the extend piece
		SnakeSegment& tail_bone = snakeBody[snakeBody.size() - 2];

		//If the position of the tail_head and the tail_bone in the x axis is the same
		if (tail_head.position.x == tail_bone.position.x) {
			//If the tail_head position is greated than the tail_bone position in the y axis, meaning is facing up
			if (tail_head.position.y > tail_bone.position.y) {
				//Push a new SnakeSegment at the end of the snakeBody vector
				//Coordinates of the new segment are: tail_head position on the x axis and tail_head position on the y axis + 1
				snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			}
			//The tail_head position is less than the tail_bone position in the y axis, meaning is facing down
			else {
				//Push a new SnakeSegment at the end of the snakeBody vector
				//Coordinates of the new segment are: tail_head position on the x axis and tail_head position on the y axis - 1
				snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}
		//If the position of the tail_head and the tail_bone in the y axis is the same
		else if (tail_head.position.y == tail_bone.position.y) {
			//If the tail_head position is greated than the tail_bone position in the x axis, meaning is facing left
			if (tail_head.position.x > tail_bone.position.x) {
				//Push a new SnakeSegment at the end of the snakeBody vector
				//Coordinates of the new segment are: tail_head position on the x axis + 1 and tail_head position on the y axis
				snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			//The tail_head position is less than the tail_bone position in the x axis, meaning is facing right
			else {
				//Push a new SnakeSegment at the end of the snakeBody vector
				//Coordinates of the new segment are: tail_head position on the x axis - 1 and tail_head position on the y axis
				snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	//The lenght of the snake is only the head, we add the new segment based on the direction the snake is going
	else {
		//Check the direction to where the snake is going
		if (direction == Direction::Up) {
			//Push a new SnakeSegment at the end of the snakeBody vector
			//Coordinates of the new segment are: tail_head position on the x axis and tail_head position on the y axis + 1
			snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}
		else if (direction == Direction::Down) {
			//Push a new SnakeSegment at the end of the snakeBody vector
			//Coordinates of the new segment are: tail_head position on the x axis and tail_head position on the y axis - 1
			snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (direction == Direction::Left) {
			//Push a new SnakeSegment at the end of the snakeBody vector
			//Coordinates of the new segment are: tail_head position on the x axis + 1 and tail_head position on the y axis
			snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}

		else if (direction == Direction::Right) {
			//Push a new SnakeSegment at the end of the snakeBody vector
			//Coordinates of the new segment are: tail_head position on the x axis -1 and tail_head position on the y axis
			snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}

/****************************************************/
/* Reset Function									*/
/* It is called every time a new game begins.		*/
/* Clears the snake segment vector from previous	*/
/* game. It will add 3 segmets (default length)		*/
/* one for the head, one for the actual body,		*/
/* and one for the tail.							*/
/****************************************************/
void Snake::Reset() {
	//Clear the body (vector<SnakeSegments>)
	snakeBody.clear();
	//Add three segments, in harcoded intial position
	snakeBody.push_back(SnakeSegment(5, 7));
	snakeBody.push_back(SnakeSegment(5, 6));
	snakeBody.push_back(SnakeSegment(5, 5));
	//Set direction to none since it is the beginning state
	SetDirection(Direction::None);
	headSprite.setTexture(headTextureDown);
	//Initial setup: speed, number of lives, score to 0, and lost variabe to false
	speed = 12;
	lives = 3;
	score = 0;
	lost = false;
}

/****************************************************/
/* CheckCollision Function							*/
/* Check if the head makes collision with the body	*/
/****************************************************/
void Snake::CheckCollision() {
	if (snakeBody.size() < 5) { return; }//If the length of the snake is less than 5, no need to check for collision
	SnakeSegment& head = snakeBody.front();//Reference of the head of the snake since it would be the first one to hit another segment
										   //Iterate over the snakeBody (vector), skip the head
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
	{
		//If the position of the current iteration (snakeSegment) is the same as the position of the head, there is a collision
		if (itr->position == head.position) {
			int segments = snakeBody.end() - itr;//Get the amount of segments to cut, from the end of the snake to the segment being hit
			Cut(segments);//Call Cut() and pass number of segments
			break;
		}
	}
}

/****************************************************/
/* Move Function									*/
/* Move the snake in the world (grid) by one space	*/
/****************************************************/
void Snake::Move() {
	//Iterate backwards over the snakeBody (vector), create an "inchworm" effect, for example, segment in position 3 moves to the position of segment 2 and so on until we get to the head.
	for (int i = snakeBody.size() - 1; i > 0; --i) {
		snakeBody[i].position = snakeBody[i - 1].position;
	}
	//Determine where to place the head of the snake
	if (direction == Direction::Left) {
		//Snake is moving left, head position will be one less than its current position in the x axis
		--snakeBody[0].position.x;
		headSprite.setTexture(headTextureLeft);
	}
	else if (direction == Direction::Right) {
		//Snake is moving right, head position will be one more than its current position in the x axis
		++snakeBody[0].position.x;
		headSprite.setTexture(headTextureRight);
	}
	else if (direction == Direction::Up) {
		//Snake is moving up, head position will be one less than its current position in the y axis
		--snakeBody[0].position.y;
		headSprite.setTexture(headTextureUp);
	}
	else if (direction == Direction::Down) {
		//Snake is moving up, head position will be one more than its current position in the y axis
		++snakeBody[0].position.y;
		headSprite.setTexture(headTextureDown);
	}
}

/****************************************************/
/* Tick Function									*/
/* Fixed time-step to move and check collision		*/
/****************************************************/
void Snake::Tick() {
	if (snakeBody.empty()) { return; }//If there's no snake, no need to update
	if (direction == Direction::None) { return; }//If the snake is not moving, no need to update
	Move();//Call Move() to move the snake
	CheckCollision();//Call CheckCollision()
}

/****************************************************/
/* Cut Function										*/
/* "Cut" the snake in case of collision				*/
/* @param l_segments Number of segments to remove	*/
/****************************************************/
void Snake::Cut(int segments) {
	//Loop the amount of segments to be removed
	for (int i = 0; i < segments; ++i) {
		snakeBody.pop_back();//Popping the element from the back of the vector
	}
	--lives;//Decrease the number of lives
	if (!lives) { Lose(); return; }//If there are no more lives left, call Lose()

	logTextbox->Add("You have lost a life! Lives left: "
		+ std::to_string((long long)lives));
}

/****************************************************/
/* Render Function									*/
/* Render the snake to the window					*/
/* @param window Reference to the window			*/
/****************************************************/
void Snake::Render(sf::RenderWindow& window) {
	if (snakeBody.empty()) { return; }

	auto head = snakeBody.begin();//Get the first element of the vector, the head
	bodyRectangle.setFillColor(sf::Color::Magenta);//Set the color of the rectangle, which represents the snake head right now
	bodyRectangle.setPosition(head->position.x * sizeBlock, head->position.y * sizeBlock); //Set the position of the rectangle to the position of the head
	headSprite.setPosition(head->position.x * sizeBlock, head->position.y * sizeBlock);
	window.draw(headSprite); //Draw the rectangle

	bodyRectangle.setFillColor(sf::Color::Blue);//Set the color again, now the rest of the body
	for (auto itr = snakeBody.begin() + 1;
		itr != snakeBody.end(); ++itr) {
		bodyRectangle.setPosition(itr->position.x * sizeBlock, itr->position.y * sizeBlock);
		bodySprite.setPosition(itr->position.x * sizeBlock, itr->position.y * sizeBlock);
		window.draw(bodySprite);
	}
}