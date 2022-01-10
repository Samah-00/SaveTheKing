#pragma once
#include "GameObject.h"

enum MOVE_STATUS
{
	S_BLOCKED = -1, S_CLEAR, S_FIRE, S_ORC, S_KEY, S_GATE, S_CHAIR, S_TELE, S_KILL_PRESENT
};

class MovingObject : public GameObject
{
public:
	MovingObject(sf::Texture& image, float x, float y) : GameObject(image, x, y), m_firstDraw(true), m_numOfLives(3) {};
	//using GameObject::GameObject;
	virtual int move(sf::Time deltaTime, const char* NextStep) = 0;
	virtual sf::Sprite& initializeImg() = 0;
	virtual void setDirection(sf::Keyboard::Key key);
	sf::Vector2f getPosition() const;
	sf::Vector2f getDirection() const;
	int getNumOfLives() const { return m_numOfLives; };

protected:
	sf::Vector2f m_direction;
	bool m_firstDraw;
	int m_numOfLives;

};