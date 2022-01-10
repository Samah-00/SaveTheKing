#include "Warrior.h"
#include <iostream>

Warrior::Warrior(sf::Texture& image, float x, float y) : MovingObject(image, x, y)
{
	m_warrior1 = image;
	m_warrior2.loadFromFile("Warrior2.png");
}


sf::Sprite& Warrior::initializeImg() {
	
	//m_image.setOrigin(sf::Vector2f(m_image.getTexture()->getSize() / 2u));
	if (m_firstDraw)
	{
		m_image.setScale(0.1f, 0.1f);
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		m_firstDraw = false;
	}
	return m_image;
};

void Warrior::draw(sf::RenderWindow& window)
{
	window.draw(initializeImg());
}

int Warrior::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = S_CLEAR; // initial move statuse:  clear way
	if (NextStep[6] == 'W' || NextStep[6] == 'F' ||
		NextStep[6] == 'G')  // 'K' = king chair
		return S_BLOCKED; // update move status: blocked way
	if (NextStep[6] == 'O')
		moveStatus = S_ORC; // 2 = moved on orc and put key instead
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

void Warrior::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
		m_image.setTexture(m_warrior2);
		m_direction = sf::Vector2f(1, 0);  break;
	case sf::Keyboard::Key::Left:
		m_image.setTexture(m_warrior1);
		m_direction = sf::Vector2f(-1, 0);  break;
	}
}