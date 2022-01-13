#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"

class Enemy : public MovingObject
{
public:
	//using MovingObject::MovingObject;
	Enemy(sf::Texture& image, float x, float y);
	sf::Sprite& initializeImg();
	void draw(sf::RenderWindow& window);
	int move(sf::Time deltaTime, const char* NextStep);
	void setDirection(int key);
	void setCurrDir(int dir) { m_currDir = dir; };
	int getCurrDir() { return m_currDir; };
	void speedUpEnemy() { m_enemySpeed *= 2; };
	void MoveEnemy(sf::Vector2u levelSize, const char* NextStep, sf::Vector2f temp);
	~Enemy() = default;

private:
	int m_currDir;
	sf::Clock m_enemyClock;
	sf::Texture m_enemy1;
	sf::Texture m_enemy2;
	float m_enemySpeed;
};