#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(sf::Texture& image, float x, float y): m_image(image) { m_position.x = x; m_position.y = y; };
	sf::Vector2f getIndex() { return m_position; };
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual sf::Sprite& initializeImg() = 0;
	virtual ~GameObject() = default;

protected:
	sf::Sprite m_image;
	sf::Vector2f m_position;
	int m_objectSizeFitter = 45;

};