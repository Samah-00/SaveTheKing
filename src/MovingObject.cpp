#include "MovingObject.h"

void MovingObject::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Up:
	case sf::Keyboard::Key::W:
		m_direction = sf::Vector2f(0,-1); break;
	case sf::Keyboard::Key::Down:
	case sf::Keyboard::Key::S:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Right:
	case sf::Keyboard::Key::D:
		m_direction = sf::Vector2f(1, 0);  break;
	case sf::Keyboard::Key::Left:
	case sf::Keyboard::Key::A:
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