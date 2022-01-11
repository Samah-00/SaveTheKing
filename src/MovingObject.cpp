#include "MovingObject.h"

void MovingObject::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0,-1); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
		m_direction = sf::Vector2f(1, 0);  break;
	case sf::Keyboard::Key::Left:

		m_direction = sf::Vector2f(-1, 0);  break;
	}
}

sf::Vector2f MovingObject::getPosition() const
{
	return m_image.getPosition();
}

sf::Vector2f MovingObject::getDirection() const
{
	return m_direction;
}