#include <typeinfo>
#include <iostream>
#include "Board.h"

Board::Board() : m_player(0), m_timer(0), m_thiefHasKey(false), m_success(false)
{
    //set background
    m_background.loadFromFile("GameBackGround.jpg");
    m_clock.restart();
    m_textures.resize(21); //20 = number of icons
    m_SoundsBuffer.resize(13);
    m_textures[KING].loadFromFile("King.png");
    m_textures[MAGE].loadFromFile("Mage.png");
    m_textures[WARRIOR].loadFromFile("Warrior.png");
    m_textures[THIEF].loadFromFile("Thief.png");
    m_textures[TELEPORT_CELL].loadFromFile("TeleportCell.png");
    m_textures[ORC].loadFromFile("Orc.png");
    m_textures[FIRE].loadFromFile("Fire.png");
    m_textures[GATE].loadFromFile("Gate2.png");
    m_textures[CHAIR].loadFromFile("KingChair.png");
    m_textures[WALL].loadFromFile("wall.jpg");
    m_textures[KEY].loadFromFile("Key.png");
    m_textures[GHOST].loadFromFile("Enemy.png");
    m_textures[UP_PRESENT].loadFromFile("UpPresent.png");
    m_textures[DOWN_PRESENT].loadFromFile("downPresent.png");
    m_textures[KILL_PRESENT].loadFromFile("killPresent.png");
    m_textures[ARROW].loadFromFile("Arrow.png");
    m_textures[LEVEL_UP].loadFromFile("LevelUp.png");
    m_textures[GAME_OVER].loadFromFile("GameOver.png");
    m_textures[HEALING_KIT].loadFromFile("HealingKitPresent.png");
    m_textures[SPEED_UP_PRESENT].loadFromFile("SpeedUpPresent.png");
    m_textures[UNLOCKED_GATE].loadFromFile("OpenGate.png");
    m_SoundsBuffer[0].loadFromFile("swordSound.wav");
    m_SoundsBuffer[1].loadFromFile("GhostSound.wav");
    m_SoundsBuffer[2].loadFromFile("teleportSound.wav");
    m_SoundsBuffer[3].loadFromFile("FireSound.wav");
    m_SoundsBuffer[4].loadFromFile("BlockedSound.wav");
    m_SoundsBuffer[5].loadFromFile("OpenGateSound1.wav");
    m_SoundsBuffer[6].loadFromFile("KeySound.wav");
    m_SoundsBuffer[7].loadFromFile("DecreaseTimeSound.wav");
    m_SoundsBuffer[8].loadFromFile("IncreaseTimeSound.wav");
    m_SoundsBuffer[9].loadFromFile("LevelUpSound.wav");
    m_SoundsBuffer[10].loadFromFile("GameOverSound.wav");
    m_SoundsBuffer[11].loadFromFile("HealingSound.wav");
    m_SoundsBuffer[12].loadFromFile("DangerSound.wav");
    InitializeSound();
}

void Board::InitializeSound()
{
    for (int index = 0; index < m_SoundsBuffer.size(); index++)
        m_Sounds.push_back(sf::Sound(m_SoundsBuffer[index]));
}

//this function reads the level board from the file
void Board::readLevel(sf::Vector2u levelSize, int timer, std::ifstream& board_file)
{
    m_levelSize = levelSize;
    m_timer = timer;
    char c;
    std::string line;

    //go back to the beginning of the file
    board_file.seekg(0);

    //ignor two lines (the sketch of the board starts from the 3rd line)
    getline(board_file, line);
    getline(board_file, line);

    //start reading the level
    for (size_t j = 0; j < m_levelSize.y; j++)
    {
        for (size_t i = 0; i <= m_levelSize.x ; i++)
        {
            c = char(board_file.get());
            if (c == 10 || c == -1) // 10 =\n , -1 = eof
                break;
            readChar(c, i, j);
        }
    }
}

//this function reads every character in the board file and creates
//the object that indicates the characte
void Board::readChar(const char c, const size_t i, size_t& j)
{
    m_board.resize(m_levelSize.y);
    for (unsigned int index = 0; index < m_levelSize.y; index++)
        m_board[index].resize(m_levelSize.x);
     
    m_characters.resize(4);

    if (c != '\n') //ignore the break
    {
        switch (c)
        {
        case D_WALL:
            m_board[j][i] = std::make_unique<Wall>(m_textures[WALL], float(i), float(j));
            break;
        case D_FIRE:
            m_board[j][i] = std::make_unique<Fire>(m_textures[FIRE], float(i), float(j));
            break;
        case D_ORC:
            m_board[j][i] = std::make_unique<Orc>(m_textures[ORC], float(i), float(j));
            break;
        case D_GATE:
            m_board[j][i] = std::make_unique<Gate>(m_textures[GATE], float(i), float(j));
            break;
        case D_TELEPORT_CELL:
            m_board[j][i] = std::make_unique<TeleportCell>(m_textures[TELEPORT_CELL], float(i), float(j));
            m_TeleportCells.emplace_back(std::make_unique<TeleportCell>(m_textures[TELEPORT_CELL], float(i), float(j)));
            break;
        case D_CHAIR:
            m_board[j][i] = std::make_unique<Chair>(m_textures[CHAIR], float(i), float(j));
            break;
        case D_UP_PRESENT:
            m_board[j][i] = std::make_unique<IncreaseTimePresent>(m_textures[UP_PRESENT], float(i), float(j));
            break;
        case D_DOWN_PRESENT:
            m_board[j][i] = std::make_unique<DecreaseTimePresent>(m_textures[DOWN_PRESENT], float(i), float(j));
            break;
        case D_KILL_PRESENT:
            m_board[j][i] = std::make_unique<executeEnemyPresent>(m_textures[KILL_PRESENT], float(i), float(j));
            break;
        case D_HEALING_KIT:
            m_board[j][i] = std::make_unique<HealingKitPresent>(m_textures[HEALING_KIT], float(i), float(j));
            break;
        case D_SPEEDUP_PRESENT:
            m_board[j][i] = std::make_unique<SpeedUpPresent>(m_textures[SPEED_UP_PRESENT], float(i), float(j));
            break;
        case D_KING:
            m_characters[KING] = std::make_unique<King>(m_textures[KING], float(i), float(j));
            break;
        case D_MAGE:
            m_characters[MAGE] = std::make_unique<Mage>(m_textures[MAGE], float(i), float(j));
            break;
        case D_WARRIOR:
            m_characters[WARRIOR] = std::make_unique<Warrior>(m_textures[WARRIOR], float(i), float(j));
            break;
        case D_THIEF:
            m_characters[THIEF] =  std::make_unique<Thief>(m_textures[THIEF], float(i), float(j));
            break;
        case D_GHOST:
            m_enemies1.emplace_back(std::make_unique<Enemy>(m_textures[GHOST], float(i), float(j)));
            break;
        default:
            break;
        }
    }
}
