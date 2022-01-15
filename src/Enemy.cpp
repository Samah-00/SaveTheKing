#include "Enemy.h"
#include <iostream>

//the c-tor for the enemy class
Enemy::Enemy(sf::Texture& image, float x, float y) : MovingObject(image, x, y), m_currDir(72), m_enemySpeed(50.f)
{
	m_direction = sf::Vector2f(1, 0);
	m_enemy1 = image;
	m_enemy2.loadFromFile("Enemy2.png");
}

//this function initializes the image of the enemy
sf::Sprite& Enemy::initializeImg() {
	m_image.setScale(0.1f, 0.1f);
	if (m_firstDraw)//if it's the first time to initialize the image then set the position of the image
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

//this function moves the enemies accoring to how much time has passed
int Enemy::move(sf::Time deltaTime, const char* NextStep)
{
	int moveStatus = 0;
	m_image.move(m_direction * m_enemySpeed * deltaTime.asSeconds());
	return moveStatus;
}

//this function sets the direction of the enemy object (right or left)
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

//this function checks the movement of the enemy and then moves it
void Enemy::MoveEnemy(sf::Vector2u levelSize, const char* NextStep, sf::Vector2f temp)
{
	const auto deltaTime = m_enemyClock.restart();
	//if the new position of the enemy is out of the range of the game then return without moving
	if (round(temp.x) >= levelSize.x || round(temp.x) < 0 ||
		round(temp.y) >= levelSize.y || round(temp.y) < 0)
		return;

	if (NextStep[0] != ' ' && !(NextStep[6] == 'H' || NextStep[6] == 'I'
		|| NextStep[6] == 'D' || NextStep[6] == 'S' || NextStep[6] == 'e'))
	{
			if (getCurrDir() == 72)
				setCurrDir(71);
			else
				setCurrDir(72);
	}
	int moveStatus = move(deltaTime, NextStep);
}