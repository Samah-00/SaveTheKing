#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"

class Mage : public MovingObject
{
public:
	Mage(sf::Texture& image, float x, float y);
	virtual sf::Sprite& initializeImg();
	void draw(sf::RenderWindow& window);
	virtual int move(sf::Time deltaTime, const char* NextStep);
	void setDirection(sf::Keyboard::Key key);

private:
	sf::Texture m_mage1;
	sf::Texture m_mage2;
};