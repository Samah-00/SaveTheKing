#include "Level.h"

Level::Level() :
    m_level(1),
    m_timer(0),
    m_levelSize(0, 0),
    m_timeLimitedLevel(false)
{
    m_GameMusic.openFromFile("GameSound.wav");
    std::ifstream levels_num_file;
    std::string line;
    levels_num_file.open("Num of levels.txt");
    getline(levels_num_file, line);
    m_num_of_levels = stoi(line);
    levels_num_file.close();
}

//This function builds the level
//it reads if the level is timelimited or not and then builds the level accordingly
void Level::buildLevel()
{
    BoardController boardController;
    m_timer = 0;
    std::ifstream board_file;
    createFileName();
    board_file.open(m_fileName);
    if (!board_file) //if opening the file faild. . .
    {
        std::cerr << "Error: File could NOT be opened !!!";
        exit(1);
    }
    std::string time_str;
    getline(board_file, time_str); //reading the data that indicates if the level is time limited or not
    if (time_str == "T") // T = time limited level, F = not time limited
    {
        m_timeLimitedLevel = true;
        getline(board_file, time_str);
        std::stringstream geek(time_str);
        float levelTimer;
        geek >> levelTimer; //the time from string to float
        m_timer = levelTimer;
    }
    else //if the level isn't time limited
    {
        m_timeLimitedLevel = false; //newww
        getline(board_file, time_str); //ignore a line
    }


    calculateLevelSize(board_file);
    Board* board = &boardController;
    board->readLevel(m_levelSize, m_timer, board_file);
    if (!boardController.startLevel(m_level, m_timeLimitedLevel))
    {
        m_level = m_level - 1; //return to the same level
    }

}

//this function creats the file name based of the number of the level we are in
std::string Level::createFileName()
{
    return (std::to_string(m_level) + ".txt");
}

//this function operates the level and runs it
void Level::levelOperator()
{
    for (; m_level <= m_num_of_levels; m_level++)//go through all the levels we have
    {
        m_GameMusic.play();
        m_levelSize.x = m_levelSize.y = 0;
        m_fileName = createFileName();
        buildLevel(); //why to make file name private? when lose/time is up
    }
}

//this function calculates each level's width and height (size)
void Level::calculateLevelSize(std::ifstream& board_file)
{
    while (!board_file.eof())
    {
        std::string line;
        getline(board_file, line);
        m_levelSize.y++;
        m_levelSize.x = ((line.size() > m_levelSize.x) ? unsigned int(line.size()) : m_levelSize.x);
    }
}