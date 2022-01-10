#include "Thief.h"

Thief::Thief(sf::Texture& image, float x, float y) : MovingObject(image, x, y), m_hasKey(false)
{
	m_thief1 = image;
	m_thief2.loadFromFile("Thief2.png");
	m_thiefWithKey1.loadFromFile("ThiefWithKey.png");
	m_thiefWithKey2.loadFromFile("ThiefWithKey2.png");
}


sf::Sprite& Thief::initializeImg() {
	
	//m_image.setOrigin(sf::Vector2f(m_image.getTexture()->getSize() / 2u));
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

int Thief::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = S_CLEAR; // initialize move status: clear
	if (NextStep[6] == 'W' || NextStep[6] == 'F' || NextStep[6] == 'O'
		|| (NextStep[6] == 'G' && !m_hasKey))  // 'K' = king chair
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
	if (NextStep[6] == 'T')
		moveStatus = S_TELE;
	if (NextStep[6] == 'e')
		moveStatus = S_KILL_PRESENT;
	if (NextStep[6] == 'I')
		moveStatus = 8;
	if (NextStep[6] == 'D')
		moveStatus = 9;
	if (NextStep[6] == 'E')
		return 10;
	if (deltaTime.asSeconds() > 3.f)
	{
		sf::Clock temp;
		deltaTime = temp.getElapsedTime();
	}
	const auto speedPerSecond = 30.f;
	m_image.move(m_direction * speedPerSecond);
	return moveStatus;
}

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