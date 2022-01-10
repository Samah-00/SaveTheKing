#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Present.h"


class IncreaseTimePresent : public Present
{
public:
	using Present::Present;
	//this function creates the image of the Fire Object and returns it
	virtual sf::Sprite& initializeImg() {
		m_image.setScale(0.15f, 0.15f);
		//m_image.setOrigin(sf::Vector2f(m_image.getTexture()->getSize() / 2u));
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		return m_image;
	};

	void draw(sf::RenderWindow& window)
	{
		window.draw(initializeImg());
	}

private:

};