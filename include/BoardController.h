#pragma once
#include "Board.h"
#include "levelData.h"

class BoardController : public Board
{
public:
	using Board::Board;
	bool startLevel(int levelNum, bool timeLimitedLevel);
	void handleKeyPressed(sf::Keyboard::Key key);
	const char* getNextStep(sf::Vector2f temp);
	void handleArrowPressed(sf::Keyboard::Key key);
	void ShowResult(sf::Texture result, sf::Sound);

private:
	int m_TimeLeft;
};