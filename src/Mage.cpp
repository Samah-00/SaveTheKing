#include "Mage.h"

Mage::Mage(sf::Texture& image, float x, float y) : MovingObject(image, x, y)
{
	m_mage1 = image;
	m_mage2.loadFromFile("Mage2.png");
}


sf::Sprite& Mage::initializeImg() {
	
	//m_image.setOrigin(sf::Vector2f(m_image.getTexture()->getSize() / 2u));
	if (m_firstDraw)
	{
		m_image.setScale(0.1f, 0.1f);
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		m_firstDraw = false;
	}
	return m_image;
};

void Mage::draw(sf::RenderWindow& window)
{
	window.draw(initializeImg());
}

int Mage::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = S_CLEAR; // move status: clear
	if (NextStep[6] == 'W' || NextStep[6] == 'O' ||
		NextStep[6] == 'G')  // 'K' = king chair
		return S_BLOCKED; // move status: blocked
	if (NextStep[6] == 'F')
		moveStatus = S_FIRE; //1 = move on fire
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

void Mage::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
		m_image.setTexture(m_mage2);
		m_direction = sf::Vector2f(1, 0);  break;
	case sf::Keyboard::Key::Left:
		m_image.setTexture(m_mage1);
		m_direction = sf::Vector2f(-1, 0);  break;
	}
}