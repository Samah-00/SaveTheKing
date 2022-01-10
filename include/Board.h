#pragma once
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Wall.h>
#include <Gate.h>
#include <Orc.h>
#include <Chair.h>
#include <TeleportCell.h>
#include <Fire.h>
#include <King.h>
#include <Mage.h>
#include <Warrior.h>
#include <Thief.h>
#include <Key.h>
#include "MovingObject.h"
#include "Enemy.h"
#include "Present.h"
#include "IncreaseTimePresent.h"
#include "DecreaseTimePresent.h"
#include "executeEnemyPresent.h"
#include "HealingKitPresent.h"
#include "SpeedUpPresent.h"

inline auto font1 = sf::Font();


enum CHARS
{
	GATE = '#', WALL = '=', GOAST = '^', TELEPORT_CELL = 'X', FIRE = '*', ORC = '!', CHAIR = '@',
	KING = 'K', MAGE = 'M', THIEF = 'T', WARRIOR = 'W',
	UP_PRESENT = '+', DOWN_PRESENT = '-', KILL_PRESENT = '~'
};

class Board
{
public:
	Board();
	void readLevel(sf::Vector2u levelSize, int timer,std::ifstream& board_file);
	void InitializeSound();

//private:
protected:
	std::vector<std::vector<std::unique_ptr<GameObject>>> m_board;
	std::vector<std::unique_ptr<MovingObject>> m_characters;
	std::vector<Enemy*> m_enemies;
	std::vector<std::unique_ptr<TeleportCell>> m_TeleportCells;
	std::vector<sf::Clock> m_enemyClock;
	std::vector<sf::SoundBuffer> m_SoundsBuffer;
	std::vector<sf::Sound> m_Sounds;
	sf::Vector2u m_levelSize;
	int m_timer;
	sf::Clock m_clock;
	sf::Clock m_moveClock;
	std::vector <sf::Texture> m_textures;
	sf::Vector2f kingPos;
	sf::Texture m_background;
	int m_player;
	bool m_thiefHasKey;
	bool m_success;
	// Helper Functions:
	void readChar(const char c, const size_t i, size_t& j);

};