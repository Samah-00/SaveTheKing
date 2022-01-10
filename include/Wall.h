#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StaticObject.h"

class Wall : public StaticObject
{
public:
	using StaticObject::StaticObject;
	//this function creates the image of the Wall Object and returns itImg;
	virtual sf::Sprite& initializeImg() {
		m_image.setScale(0.1f, 0.1f);
		//m_image.setOrigin(sf::Vector2f(m_image.getTexture()->getSize() / 2u));
		m_image.setPosition(m_image.getGlobalBounds().width * m_position.x, m_image.getGlobalBounds().height * m_position.y);
		return m_image;
	};

	void draw(sf::RenderWindow& window)
	{
		window.draw(initializeImg());
	}

private:

};