#include "Thief.h"

//the c-tor for the Thief class
Thief::Thief(sf::Texture& image, float x, float y) : MovingObject(image, x, y), m_hasKey(false)
{
	m_thief1 = image;
	m_thief2.loadFromFile("Thief2.png");
	m_thiefWithKey1.loadFromFile("ThiefWithKey.png");
	m_thiefWithKey2.loadFromFile("ThiefWithKey2.png");
}

//this function initializes the image of the thief and returns the image updated
sf::Sprite& Thief::initializeImg() {
	if (m_firstDraw)
	{
		m_image.setScale(0.1f, 0.1f);
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		m_firstDraw = false;
	}
	return m_image;
};

void Thief::draw(sf::RenderWindow& window)
{
	window.draw(initializeImg());
}

//this function checks the movement of the thief and then moves it accoring to the check
//and returns the status of the movement to make the neccesery changes and updates on the game
int Thief::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = S_CLEAR; // initialize move status: clear
	if (NextStep[6] == 'W' || NextStep[6] == 'F' || NextStep[6] == 'O'
		|| (NextStep[6] == 'G' && !m_hasKey))  //the character saw a wall, or fire, or orc, or gate
		return S_BLOCKED; // update move status: blocked
	if (NextStep[6] == 'K')
	{
		moveStatus = S_KEY;
		m_hasKey = true;
	}
	if (NextStep[6] == 'G' && m_hasKey)
	{
		m_hasKey = false;
		moveStatus = S_GATE;// 4 = opened the gate
	}
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
		m_numOfLives++;//increase the number of lives that the king has
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


//this function sets the direction of the thief based on the arrow key that has been pressed
void Thief::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
		if (m_hasKey)
			m_image.setTexture(m_thiefWithKey2);
		else
			m_image.setTexture(m_thief2);
		m_direction = sf::Vector2f(1, 0);  break;
	case sf::Keyboard::Key::Left:
		if (m_hasKey)
			m_image.setTexture(m_thiefWithKey1);
		else
			m_image.setTexture(m_thief1);
		m_direction = sf::Vector2f(-1, 0);  break;
	}
}