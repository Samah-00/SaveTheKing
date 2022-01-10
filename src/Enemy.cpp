#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Texture& image, float x, float y) : MovingObject(image, x, y), m_currDir(72)
{
	m_enemy1 = image;
	m_enemy2.loadFromFile("Enemy2.png");
}


sf::Sprite& Enemy::initializeImg() {
	m_image.setScale(0.1f, 0.1f);
	//m_image.setOrigin(sf::Vector2f(m_image.getTexture()->getSize() / 2u));
	if (m_firstDraw)
	{
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		m_firstDraw = false;
	}
	return m_image;
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(initializeImg());
}

int Enemy::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = 0;
	const auto speedPerSecond = 30.f;
	m_image.move(m_direction * speedPerSecond * deltaTime.asSeconds());
	return moveStatus;
}

void Enemy::setDirection(int key)
{
	switch (key)
	{
	case 72:
		m_image.setTexture(m_enemy2);
		m_direction = sf::Vector2f(1, 0); break;
	case 71:
		m_image.setTexture(m_enemy1);
		m_direction = sf::Vector2f(-1, 0); break;
	}
}