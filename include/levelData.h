#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class LevelData
{
public:
	LevelData(int, sf::Vector2u);
	void draw(sf::RenderWindow& window, sf::Clock);
	void initializeData(int player, bool key, int timeLeft, bool timeLimitedLevel);
	void updateLevelData(sf::Clock);
	void setDataDesign();
	void NameOfCharacter();


private:
	sf::Font m_font;
	std::vector<sf::Text> m_titels;
	std::vector<sf::Text> m_data;
	int m_levelNum;
	int m_player;
	bool m_thiefHasKey;
	std::string m_keyData;
	sf::Vector2u m_levelSize;
	std::string m_currCharacter;
	int m_timeLeft;
	bool m_timeLimitedLevel;
};