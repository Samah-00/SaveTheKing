#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"

class Thief : public MovingObject
{
public:
	Thief(sf::Texture& image, float x, float y);
	using MovingObject::MovingObject;
	virtual sf::Sprite& initializeImg();
	void draw(sf::RenderWindow& window);
	virtual int move(sf::Time deltaTime, const char* NextStep);
	void setDirection(sf::Keyboard::Key key);

private:
	bool m_hasKey;
	sf::Texture m_thief1;
	sf::Texture m_thief2;
	sf::Texture m_thiefWithKey1;
	sf::Texture m_thiefWithKey2;
};