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
#include "UnlockedGate.h"

inline auto font1 = sf::Font();

enum CHARS_DICTIONARY // D for dictionary
{
	D_GATE = '#', D_WALL = '=', D_GHOST = '^', D_TELEPORT_CELL = 'X', D_FIRE = '*', D_ORC = '!', D_CHAIR = '@',
	D_KING = 'K', D_MAGE = 'M', D_THIEF = 'T', D_WARRIOR = 'W',
	D_UP_PRESENT = '+', D_DOWN_PRESENT = '-', D_KILL_PRESENT = '/', D_HEALING_KIT = '$', D_SPEEDUP_PRESENT = 'S'
};

enum CHARS
{
	KING, MAGE, WARRIOR, THIEF, GATE, WALL, GHOST, TELEPORT_CELL, FIRE , ORC , CHAIR ,
	UP_PRESENT , DOWN_PRESENT , KILL_PRESENT , HEALING_KIT, SPEED_UP_PRESENT, KEY,
	ARROW, LEVEL_UP, GAME_OVER, UNLOCKED_GATE
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
	const int m_iconSize = 45;
	// Helper Functions:
	void readChar(const char c, const size_t i, size_t& j);

};