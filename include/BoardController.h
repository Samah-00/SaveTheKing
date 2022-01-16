#pragma once
#include "Board.h"
#include "levelData.h"

const int INFO = 150;

class BoardController : public Board
{
public:
	using Board::Board;
	bool startLevel(int levelNum, bool timeLimitedLevel);
	void drawMap(sf::RenderWindow& window);
	void handleKeyPressed(sf::Keyboard::Key key);
	const char* getNextStep(sf::Vector2f temp);
	void handleArrowPressed(sf::Keyboard::Key key);
	void handleNextStep(sf::Vector2f temp);
	void ShowResult(sf::Texture result, sf::Sound);

private:
	int m_TimeLeft;
	sf::Sprite m_backgroundImg;
	sf::Sprite m_arrow;
};