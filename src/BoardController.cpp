#include "BoardController.h"

//this function starts the level, creates the window and prints the level on it
bool BoardController::startLevel(int LevelNum, bool timeLimitedLevel)
{
    std::string titel = "Save The King - Level " + std::to_string(LevelNum);
    sf::RenderWindow window(sf::VideoMode(m_levelSize.x * m_iconSize, m_levelSize.y * m_iconSize + 150), titel); // 150 : add space for level info
    font1.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    auto backgroundImg = sf::Sprite(m_background);
    auto arrow = sf::Sprite(m_textures[ARROW]);
    //backgroundImg.scale((m_levelSize.x * 450), (m_levelSize.y * 450));
    LevelData levelData(LevelNum, m_levelSize);
    m_enemyClock.resize(m_enemies.size());
    while (window.isOpen())
    {
        float arrowPos_x = m_characters[m_player]->getPosition().x + 10;
        float arrowPos_y = m_characters[m_player]->getPosition().y + m_iconSize;
        arrow.setPosition(arrowPos_x, arrowPos_y);
        if (m_success)
        {
            ShowResult(m_textures[LEVEL_UP], m_Sounds[9]);
            window.close();
        }
            
        window.clear();
        window.draw(backgroundImg);
        for (size_t j = 0; j < m_levelSize.y; j++)
            for (size_t i = 0; i < m_levelSize.x; i++)
                //ignore nullptr elements and print other elements to the window
                if (m_board[j][i] != nullptr)
                    if (typeid(*m_board[j][i]).name()[6] != 'E')
                        m_board[j][i]->draw(window);

        for (int index = 0; index < m_characters.size(); index++)
            m_characters[index]->draw(window);

        window.draw(arrow);

        for (int index = 0; index < m_enemies.size(); index++)
        {
            MoveEnemy(index);
            m_enemies[index]->draw(window);
        }
        
        m_clock.getElapsedTime();
        m_TimeLeft = int(m_timer - m_clock.getElapsedTime().asSeconds());
        levelData.initializeData(m_player, m_thiefHasKey, m_TimeLeft, timeLimitedLevel, m_characters[m_player]->getNumOfLives());
        levelData.draw(window, m_clock);
        window.display();
        if ((timeLimitedLevel && m_TimeLeft == 0) || m_characters[m_player]->getNumOfLives() == 0)
        {
            ShowResult(m_textures[GAME_OVER], m_Sounds[10]);
            return m_success;
        }
        if (auto event = sf::Event{}; window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: //if the user closes the window then close the window and exit
                window.close();
                break;
            case sf::Event::KeyPressed:
                handleKeyPressed(event.key.code);
                break;
            }
        }
    }
}

void BoardController::ShowResult(sf::Texture result, sf::Sound sound)
{
    sf::RenderWindow resultWindow(sf::VideoMode(result.getSize().x, result.getSize().y), " ** LEVEL\'S RESULT ** ");
    sf::Sprite resultImg(result);
    sound.play();
    while (resultWindow.isOpen())
    {
        resultWindow.clear();
        resultWindow.draw(resultImg);
        resultWindow.display();

        if (auto event = sf::Event{}; resultWindow.waitEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
            case sf::Event::KeyPressed:
                resultWindow.close();
                break;
            }
    }
}

void BoardController::handleKeyPressed(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Key::P:
        m_player = (m_player == 3) ? 0 : m_player + 1;
        break;
    case sf::Keyboard::Key::Down: case sf::Keyboard::Key::Up:
    case sf::Keyboard::Key::Left: case sf::Keyboard::Key::Right:
        handleArrowPressed(key);
        break;
    }
}

void BoardController::MoveEnemy(int enemyIndex)
{
    const auto deltaTime = m_enemyClock[enemyIndex].restart();
    m_enemies[enemyIndex]->setDirection(m_enemies[enemyIndex]->getCurrDir());
    sf::Vector2f pos(m_enemies[enemyIndex]->getPosition().x / m_iconSize, m_enemies[enemyIndex]->getPosition().y / m_iconSize);
    sf::Vector2f dir(m_enemies[enemyIndex]->getDirection().x, m_enemies[enemyIndex]->getDirection().y);
    sf::Vector2f temp = pos + dir;
    if (round(temp.x) >= m_levelSize.x || round(temp.x) < 0 ||
        round(temp.y) >= m_levelSize.y || round(temp.y) < 0)
        return;
    const char* NextStep = getNextStep(deltaTime, temp);
    //std::cout << NextStep << std::endl;
    if (NextStep[0] != ' ')
    {
        if (m_enemies[enemyIndex]->getCurrDir() == 72)
            m_enemies[enemyIndex]->setCurrDir(71);
        else
            m_enemies[enemyIndex]->setCurrDir(72);
    }
    int moveStatus = m_enemies[enemyIndex]->move(deltaTime, NextStep);
    
    if (NextStep[0] == ' ')
        m_board[round(temp.y)][round(temp.x)] =
            std::move(m_board[round(m_enemies[enemyIndex]->getIndex().y)][round(m_enemies[enemyIndex]->getIndex().x)]);
}

void BoardController::handleArrowPressed(sf::Keyboard::Key key)
{
    const auto deltaTime = m_moveClock.restart();
    m_characters[m_player]->setDirection(key);
    sf::Vector2f pos(m_characters[m_player]->getPosition().x / m_iconSize, m_characters[m_player]->getPosition().y / m_iconSize);
    sf::Vector2f dir(m_characters[m_player]->getDirection().x * 0.3f , m_characters[m_player]->getDirection().y * 0.3f);
    sf::Vector2f temp = pos + dir;
    if (round(temp.x) >= m_levelSize.x || round(temp.x) < 0 ||
        round(temp.y) >= m_levelSize.y || round(temp.y) < 0)
        return;
    const char* NextStep = getNextStep(deltaTime, temp);
    int moveStatus = m_characters[m_player]->move(deltaTime, NextStep);
    switch (moveStatus)
    {
    case S_BLOCKED:
        m_Sounds[4].play();
        break;
    case S_FIRE:
        m_Sounds[3].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        break;
    case S_ORC:
        m_Sounds[0].play();
        m_board[round(temp.y)][round(temp.x)] = std::make_unique<Key>(m_textures[KEY], float(round(temp.x)), float(round(temp.y)));
        break;
    case S_KEY:
        m_Sounds[6].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_thiefHasKey = true;
        break;
    case S_GATE:
        m_Sounds[5].play();
        m_board[round(temp.y)][round(temp.x)] = std::make_unique<UnlockedGate>(m_textures[UNLOCKED_GATE], float(round(temp.x)), float(round(temp.y)));
        m_thiefHasKey = false;
        break;
    case S_CHAIR:
        m_success = true;
        break;
    case S_TELE:
        m_Sounds[2].play();
        for (int index = 0; index < m_TeleportCells.size(); index++)
        {
            sf::Vector2f Ttemp(round(temp.x) * m_iconSize, round(temp.y) * m_iconSize);
            if (m_TeleportCells[index]->initializeImg().getPosition() == Ttemp)
            {
                int SecondTeleportIndex = (index % 2 == 0) ? index + 1 : index - 1 ;
                sf::Vector2f characterPos(m_TeleportCells[SecondTeleportIndex]->initializeImg().getPosition().x - 10,
                    m_TeleportCells[SecondTeleportIndex]->initializeImg().getPosition().y - 10);
                m_characters[m_player]->initializeImg().setPosition(characterPos);
            }
        }
        break;
    case S_KILL_PRESENT:
        m_Sounds[0].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_enemies.clear();
        break;
    case S_EXTRA_TIME_PRESENT:
        m_Sounds[8].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_timer += 5;
        break;
    case S_LESS_TIME_PRESENT:
        m_Sounds[7].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_timer -= 5;
        break;
    case S_GHOST:
        m_Sounds[1].play();
        break;
    case S_HEALING_KIT:
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        break;
    case S_SPEEDUP_PRESENT:
    {
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        for (int index = 0; index < m_enemies.size(); index++)
        {
            m_enemies[index]->speedUpEnemy();
        }
    }
        
        break;
    }
}
const char* BoardController::getNextStep(sf::Time deltaTime, sf::Vector2f temp)
{
    const char* NextStep = " ";
    if (m_board[round(temp.y)][round(temp.x)] != nullptr)
        NextStep = typeid(*m_board[round(temp.y)][round(temp.x)]).name();
    for (int index = 0 ; index < m_enemies.size(); index++)
    {
        sf::Vector2f temp2 = m_enemies[index]->getPosition() / float(m_iconSize);
            if (temp2.x - 0.5f <= temp.x && temp.x <= temp2.x + 0.5f &&
                temp2.y - 0.5f <= temp.y && temp.y <= temp2.y + 0.5f)
            NextStep = "class Enemy";
    }
    return NextStep;
}