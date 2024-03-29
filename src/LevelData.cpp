#include "LevelData.h"

//the c-tor for the LevelData class, it initializes the variables of the level's data
LevelData::LevelData(int level, sf::Vector2u levelSize) : m_levelNum(level),
m_levelSize(levelSize),
m_player(0),
m_thiefHasKey(false),
m_timeLeft(0),
m_numOfLives(3),
m_timeLimitedLevel(false)
{
	m_font.loadFromFile("C:/Windows/Fonts/broadw.ttf");
}

//this function initializes the data for the level before showing it
void LevelData::initializeData(int player, bool key, int timeLeft, bool timeLimitedLevel, int lives)
{
	m_player = player; //setting the current player
	m_thiefHasKey = key; //identifying if the thief has a key at the moment or not
	m_timeLeft = timeLeft; //setting how much time is left for the level to end
	m_timeLimitedLevel = timeLimitedLevel; //identifying if the level we're in is a time limited level or not
	m_numOfLives = lives; //setting how many lives is left for the character that's playing now
}

//this function prints the level's data on the window
void LevelData::draw(sf::RenderWindow& window, sf::Clock clock)
{
	updateLevelData(clock);
	setDataDesign();
	for (int index = 0; index < m_titels.size(); index++) {
		window.draw(m_titels[index]);
		window.draw(m_data[index]);
	}
	m_titels.clear();
	m_data.clear();
}

//this function keeps updating the data every moment to keep the knfo up to date
void LevelData::updateLevelData(sf::Clock clock)
{
	NameOfCharacter(); // update the name of the current character
	m_keyData = (m_thiefHasKey ? "Yes" : "No");

	m_titels.push_back(sf::Text("Level No.", m_font));
	m_titels.push_back(sf::Text("Playing Now", m_font));
	m_titels.push_back(sf::Text("Have key?", m_font));
	m_titels.push_back(sf::Text("Num Of Lives", m_font));
	m_titels.push_back(sf::Text("Time passed", m_font));
	if (m_timeLimitedLevel)
		m_titels.push_back(sf::Text("Time left", m_font));
	m_data.push_back(sf::Text(std::to_string(m_levelNum), m_font));
	m_data.push_back(sf::Text(m_currCharacter, m_font));
	m_data.push_back(sf::Text(m_keyData, m_font));
	m_data.push_back(sf::Text(std::to_string(m_numOfLives), m_font));
	m_data.push_back(sf::Text(std::to_string(int(clock.getElapsedTime().asSeconds())), m_font));
	if (m_timeLimitedLevel)
		m_data.push_back(sf::Text(std::to_string(m_timeLeft), m_font));
}

//this function prepares the design and location of the level's data
void LevelData::setDataDesign()
{
	int num_of_data = m_timeLimitedLevel ? 6 : 5;
	for (int counter = 0; counter < m_titels.size(); counter++) {
		sf::Vector2f titelLoc(float(((m_levelSize.x * 45) / num_of_data) * counter), float(45 * m_levelSize.y));
		m_titels[counter].setPosition(titelLoc);
		m_titels[counter].setCharacterSize(20);
		float X_Data = titelLoc.x + (m_titels[counter].getGlobalBounds().width / 2); // (m_titels[counter].getLocalBounds().width / 2) is the middle of the titel
		float Y_Data = float(45 * m_levelSize.y) + 25; // +25 is the line under the line of the titel
		sf::Vector2f dataLoc(X_Data, Y_Data);
		m_data[counter].setPosition(dataLoc);
		m_data[counter].setCharacterSize(20);
		if (counter == m_titels.size()-1 && m_timeLimitedLevel && m_timeLeft < 10) // if time left < 20 sec. colour of timer = red 
			m_data[counter].setFillColor(sf::Color::Red);
	}
}

//this function determine the name of the character that is playing based on its index
void LevelData::NameOfCharacter()
{
	switch (m_player)
	{
	case 0: m_currCharacter = "King"; break;
	case 1: m_currCharacter = "Mage"; break;
	case 2: m_currCharacter = "Warrior"; break;
	case 3: m_currCharacter = "Thief"; break;
	}
}