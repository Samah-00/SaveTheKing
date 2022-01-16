#include "BoardController.h"

//this function starts the level, creates the window and prints the level on it
bool BoardController::startLevel(int LevelNum, bool timeLimitedLevel)
{
    std::string titel = "Save The King - Level " + std::to_string(LevelNum);
    sf::RenderWindow window(sf::VideoMode(m_levelSize.x * m_iconSize, m_levelSize.y * m_iconSize + INFO), titel); // INFO : space for level info
    font1.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    m_backgroundImg = sf::Sprite(m_background);
    m_arrow = sf::Sprite(m_textures[ARROW]);
    LevelData levelData(LevelNum, m_levelSize);

    while (window.isOpen()) {
        if (m_success) {
            ShowResult(m_textures[LEVEL_UP], m_Sounds[9]);
            window.close(); }
        window.clear();
        drawMap(window);

        m_clock.getElapsedTime();//calculating the clock and the timer for the level and updating it
        m_TimeLeft = int(m_timer - m_clock.getElapsedTime().asSeconds());
        levelData.initializeData(m_player, m_thiefHasKey, m_TimeLeft, timeLimitedLevel, m_characters[m_player]->getNumOfLives());
        levelData.draw(window, m_clock);//printing the level's data after updating it

        window.display();
        //the player loses if: 1.Time is up. 2.the character ended its lives
        if ((timeLimitedLevel && m_TimeLeft == 0) || m_characters[m_player]->getNumOfLives() == 0)
        { //if the player lost the game then show a result message and exit
            ShowResult(m_textures[GAME_OVER], m_Sounds[10]);
            return m_success;
        }
        if (auto event = sf::Event{}; window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed: //if the user closes the window then close the window and exit
                window.close(); break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape){
                    window.close(); exit(1); }
                handleKeyPressed(event.key.code); break;
            }
    }
    return m_success;
}

//this function draws the map of the level on the window that is recieved
void BoardController::drawMap(sf::RenderWindow& window)
{
    window.draw(m_backgroundImg);

    for (size_t j = 0; j < m_levelSize.y; j++) //drawing the board
        for (size_t i = 0; i < m_levelSize.x; i++)
            //ignore nullptr elements and print other elements to the window
            if (m_board[j][i] != nullptr)
                if (typeid(*m_board[j][i]).name()[6] != 'E')
                    m_board[j][i]->draw(window);
    //drawing the main chracters
    for (int index = 0; index < m_characters.size(); index++)
        m_characters[index]->draw(window);
    // draw enemy
    for (int index = 0; index < m_enemies1.size(); index++) {
        m_enemies1[index]->setDirection(m_enemies1[index]->getCurrDir());
        sf::Vector2f pos(m_enemies1[index]->getPosition().x / m_iconSize, m_enemies1[index]->getPosition().y / m_iconSize);
        sf::Vector2f dir(m_enemies1[index]->getDirection().x, m_enemies1[index]->getDirection().y);
        sf::Vector2f temp = pos + dir;
        const char* NextStep = getNextStep(temp);
        m_enemies1[index]->MoveEnemy(m_levelSize, NextStep, temp);
        m_enemies1[index]->draw(window);
    }
    // draw character indicator arrow
    float arrowPos_x = m_characters[m_player]->getPosition().x + 10;
    float arrowPos_y = m_characters[m_player]->getPosition().y + m_iconSize;
    m_arrow.setPosition(arrowPos_x, arrowPos_y);
    window.draw(m_arrow);
}

//this function shows the result of the level after finishing it (either win or lost)
void BoardController::ShowResult(sf::Texture result, sf::Sound sound)
{
    sf::RenderWindow resultWindow(sf::VideoMode(result.getSize().x, result.getSize().y), " ** LEVEL\'S RESULT ** ");
    sf::Sprite resultImg(result);
    sound.play();
    while (resultWindow.isOpen()) {
        resultWindow.clear();
        resultWindow.draw(resultImg);
        resultWindow.display();
        if (auto event = sf::Event{}; resultWindow.waitEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
            case sf::Event::KeyPressed:
                resultWindow.close(); break;
            }
    }
}

//this function handles the case if any key on the keyboard is pressed
void BoardController::handleKeyPressed(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Key::P: //if the pressed key is "P" then change the character playing
        m_player = (m_player == 3) ? 0 : m_player + 1; break;
    case sf::Keyboard::Key::Down: case sf::Keyboard::Key::Up:
    case sf::Keyboard::Key::Left: case sf::Keyboard::Key::Right:
        handleArrowPressed(key); break; //if the pressed key is one of the arrows to move the characters
    }
}

//this function handles the case if one of the aroows on the keyboard is pressed
void BoardController::handleArrowPressed(sf::Keyboard::Key key)
{
    m_characters[m_player]->setDirection(key); //set the new direction of the playing character
    sf::Vector2f pos(m_characters[m_player]->getPosition().x / m_iconSize, m_characters[m_player]->getPosition().y / m_iconSize);
    sf::Vector2f dir(m_characters[m_player]->getDirection().x * 0.3f , m_characters[m_player]->getDirection().y * 0.3f);
    sf::Vector2f temp = pos + dir; //the new location that the character will go to
    if (round(temp.x) >= m_levelSize.x || round(temp.x) < 0 ||
        round(temp.y) >= m_levelSize.y || round(temp.y) < 0)
        return;
    handleNextStep(temp); //check the new location
}

//this function checks the location that the character wants to go to and handles every case
void BoardController::handleNextStep(const sf::Vector2f temp)
{
    const auto deltaTime = m_moveClock.restart();
    const char* NextStep = getNextStep(temp); //get the object in the new location
    int moveStatus = m_characters[m_player]->move(deltaTime, NextStep);//move the character and return the moving status
    switch (moveStatus) //handle every status the was returned from moving the character
    {
    case S_BLOCKED: //the character found that its way is blocked
        m_Sounds[4].play(); break;
    case S_FIRE: //the character found that in its way there is fire
        m_Sounds[3].play(); //deleting the fire
        m_board[round(temp.y)][round(temp.x)] = nullptr; break;
    case S_ORC: //the character found that in its way there is a orc
        m_Sounds[0].play();//put a key after killing the orc
        m_board[round(temp.y)][round(temp.x)] = std::make_unique<Key>(m_textures[KEY], float(round(temp.x)), float(round(temp.y))); break;
    case S_KEY: //the character found that in its way there is a key
        if (!m_thiefHasKey) { //take the key only if the thief doesn't have a key in that moment
            m_Sounds[6].play();
            m_board[round(temp.y)][round(temp.x)] = nullptr;
            m_thiefHasKey = true; } break;
    case S_GATE: //the character found that in its way there is a gate
        m_Sounds[5].play();
        m_board[round(temp.y)][round(temp.x)] = std::make_unique<UnlockedGate>(m_textures[UNLOCKED_GATE], float(round(temp.x)), float(round(temp.y)));
        m_thiefHasKey = false; break;
    case S_CHAIR: //the character found that in its way there is a chair(the king's castle)
        m_success = true; break;
    case S_TELE: //the character found that in its way there is a teleport cell
        m_Sounds[2].play();
        for (int index = 0; index < m_TeleportCells.size(); index++)
        { //finding the other cell that the character should get out of
            sf::Vector2f Ttemp(round(temp.x) * m_iconSize, round(temp.y) * m_iconSize);
            if (m_TeleportCells[index]->initializeImg().getPosition() == Ttemp) {
                int SecondTeleportIndex = (index % 2 == 0) ? index + 1 : index - 1;
                sf::Vector2f characterPos(m_TeleportCells[SecondTeleportIndex]->initializeImg().getPosition().x - 10,
                    m_TeleportCells[SecondTeleportIndex]->initializeImg().getPosition().y - 10);// 10 => so the character is beside the cell
                m_characters[m_player]->initializeImg().setPosition(characterPos);//teleport the character to that other cell
            } } break;
    case S_KILL_PRESENT: //the character found that in its way there is a kill present
        m_Sounds[0].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_enemies1.clear(); break; //kill all enemies
    case S_EXTRA_TIME_PRESENT: //the character found that in its way there is increase time present
        m_Sounds[8].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_timer += 5; break;
    case S_LESS_TIME_PRESENT: //the character found that in its way there is decrease time present
        m_Sounds[7].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        m_timer -= 5; break;
    case S_GHOST: //the character found that in its way there is a ghost
        m_Sounds[1].play(); break;
    case S_HEALING_KIT: //the character found that in its way there is a healing kit present
        m_Sounds[11].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr; break;
    case S_SPEEDUP_PRESENT: //the character found that in its way there is a speed up the enemies(ghosts) present
        m_Sounds[12].play();
        m_board[round(temp.y)][round(temp.x)] = nullptr;
        for (int index = 0; index < m_enemies1.size(); index++)//speed up all the enemies(ghosts) in the game
            m_enemies1[index]->speedUpEnemy(); break;
    }
}

//this function gets the objects that exists in the new location that the character wants to go to
const char* BoardController::getNextStep(sf::Vector2f temp)
{
    const char* NextStep = " ";
    if (m_board[round(temp.y)][round(temp.x)] != nullptr)
        NextStep = typeid(*m_board[round(temp.y)][round(temp.x)]).name();
    for (int index = 0 ; index < m_enemies1.size(); index++) {  //check if the character in front is an enemy(ghost)
        sf::Vector2f temp2 = m_enemies1[index]->getPosition() / float(m_iconSize);
            if (temp2.x - 0.5f <= temp.x && temp.x <= temp2.x + 0.5f &&
                temp2.y - 0.5f <= temp.y && temp.y <= temp2.y + 0.5f)
            NextStep = "class Enemy";
    }
    return NextStep;
}