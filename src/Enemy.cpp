#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Texture& image, float x, float y) : MovingObject(image, x, y), m_currDir(72), m_enemySpeed(50.f)
{
	m_direction = sf::Vector2f(1, 0);
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
	//std::cout << m_direction.x << " " << m_direction.y << std::endl;

	//m_image.move(m_direction * m_enemySpeed);
	//std::cout << m_image.getPosition().x << " " << m_image.getPosition().y << std::endl;
	return m_image;
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(initializeImg());
}

int Enemy::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = 0;
	m_image.move(m_direction * m_enemySpeed * deltaTime.asSeconds());
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

void Enemy::MoveEnemy(sf::Vector2u levelSize, const char* NextStep, sf::Vector2f temp)
{
	const auto deltaTime = m_enemyClock.restart();
	if (round(temp.x) >= levelSize.x || round(temp.x) < 0 ||
		round(temp.y) >= levelSize.y || round(temp.y) < 0)
		return;
	if (NextStep[0] != ' ')
	{
		if (getCurrDir() == 72)
			setCurrDir(71);
		else
			setCurrDir(72);
	}
	int moveStatus = move(deltaTime, NextStep);
}