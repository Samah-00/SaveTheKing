#include "King.h"
#include <iostream>

//the c-tor for the King class
King::King(sf::Texture& image, float x, float y) : MovingObject(image, x, y)
{
	m_king1 = image;
	m_king2.loadFromFile("King2.png");
}

//this function initializes the image of the king and returns the image updated
sf::Sprite& King::initializeImg()
{
	if (m_firstDraw)
	{
		m_image.setScale(0.1f, 0.1f);
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		m_firstDraw = false;
	}
	return m_image;
}

void King::draw(sf::RenderWindow& window)
{
	window.draw(initializeImg());
}

//this function checks the movement of the king and then moves it accoring to the check
//and returns the status of the movement to make the neccesery changes and updates on the game
int King::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = S_CLEAR; // initial move status: clear way 
	if (NextStep[6] == 'W' || NextStep[6] == 'F' ||
		NextStep[6] == 'O' || NextStep[6] == 'G')  //the character saw a wall, or fire, or orc, or gate
		return S_BLOCKED; // update move status: blocked way
	if (NextStep[6] == 'C') //the new location is a chair
		moveStatus = S_CHAIR;
	if (NextStep[6] == 'T') //the new location is a teleport cell
		moveStatus = S_TELE;
	if (NextStep[6] == 'e') //the new location is a kill present
		moveStatus = S_KILL_PRESENT;
	if (NextStep[6] == 'I') //the new location is an increase time present
		moveStatus = S_EXTRA_TIME_PRESENT;
	if (NextStep[6] == 'D') //the new location is a decrease time present
		moveStatus = S_LESS_TIME_PRESENT;
	if (NextStep[6] == 'E') //the new location is an enemy(ghost)
	{
		m_numOfLives--; //decrease the number of lives that the king has
		return S_GHOST;
	}
	if (NextStep[6] == 'H') //the new location is a healing kit present
	{
		m_numOfLives++;  //increase the number of lives that the king has
		moveStatus = S_HEALING_KIT;
	}
		
	if (NextStep[6] == 'S') //the new location is a speed up present
		moveStatus = S_SPEEDUP_PRESENT;
		
	if (deltaTime.asSeconds() > 3.f)
	{
		sf::Clock temp;
		deltaTime = temp.getElapsedTime();
	}
	const auto speedPerSecond = 30.f;
	m_image.move(m_direction * speedPerSecond);
	return moveStatus;
}

//this function sets the direction of the king based on the arrow key that has been pressed
void King::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
		m_image.setTexture(m_king2);
		m_direction = sf::Vector2f(1, 0);  break;
	case sf::Keyboard::Key::Left:
		m_image.setTexture(m_king1);
		m_direction = sf::Vector2f(-1, 0);  break;
	}
}