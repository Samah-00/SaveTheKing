#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"

class Gate : public StaticObject
{
public:
	using StaticObject::StaticObject;
	//this function creates the image of the Gate Object and returns it
	virtual sf::Sprite& initializeImg() {
		m_image.setScale(0.1f, 0.1f);
		m_image.setPosition(m_objectSizeFitter * m_position.x, m_objectSizeFitter * m_position.y);
		return m_image;
	};

	void draw(sf::RenderWindow& window)
	{
		window.draw(initializeImg());
	}

private:

};