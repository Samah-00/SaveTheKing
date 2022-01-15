#include "HomePage.h"
#include <thread>
#include <iostream>

enum _CONSTS { BUTTONS = 3 };

enum Buttons { START_GAME, SHOW_HELP, EXIT_GAME, NONE };

//The c-tor of HomePage sets the width and height of the window of the HomePage
//and creates the buttons that are shown on the screen
HomePage::HomePage(int width, int height)
{
	// set window dimentions
	m_dimentions.x = float(width);
	m_dimentions.y = float(height);
	// load buttons images and sound
	m_startGame.loadFromFile("Start Button.png");
	m_help.loadFromFile("Help Button.png");
	m_exitGame.loadFromFile("Exit Button.png");
	m_startGame2.loadFromFile("Start Button Clicked.png");
	m_help2.loadFromFile("Help Button Clicked.png");
	m_exitGame2.loadFromFile("Exit Button Clicked.png");
	// set sounds
	m_homePageMusic.openFromFile("HomePageSound.wav");
	m_buttonSoundBuf.loadFromFile("ButtonClickedSound.wav");
	m_buttonSound = sf::Sound(m_buttonSoundBuf);
	// sprite images and save them in vectors
	initializeButtonsVecs();
	// adjust the images to the window
	initializeImage();
}

//this function prepares and initilize the menu buttons
void HomePage::initializeButtonsVecs()
{
	auto startImg = sf::Sprite(m_startGame);
	auto startImg2 = sf::Sprite(m_startGame2);
	auto helpImg = sf::Sprite(m_help);
	auto helpImg2 = sf::Sprite(m_help2);
	auto exitImg = sf::Sprite(m_exitGame);
	auto exitImg2 = sf::Sprite(m_exitGame2);

	m_homeButtonsVec.resize(4);
	for (int vec = 0; vec < m_homeButtonsVec.size(); vec++)
	{
		if (vec == 1) // vec 1: the buttons when the mouse cursor is on "start" button
			m_homeButtonsVec[1].push_back(startImg2);
		else m_homeButtonsVec[vec].push_back(startImg);
		if (vec == 2) // vec 2: the buttons when the mouse cursor is on "help" button
			m_homeButtonsVec[2].push_back(helpImg2);
		else m_homeButtonsVec[vec].push_back(helpImg);
		if (vec == 3) // vec 3: the buttons when the mouse cursor is on "exit" button
			m_homeButtonsVec[3].push_back(exitImg2);
		else m_homeButtonsVec[vec].push_back(exitImg);
	}
}

void HomePage::playMusic()
{
	m_homePageMusic.play();
	m_homePageMusic.setLoop(true);
}

void HomePage::stopMusic()
{
	m_homePageMusic.stop();
}

//this function initialize the images of the button
void HomePage::initializeImage()
{
	for (int vec = 0; vec < 4; vec++)
		for (int counter = 0; counter < BUTTONS; counter++)
		{
			sf::Vector2f toolLoc(float(m_dimentions.x / 2), float((m_dimentions.y / 6) * (counter + 1) + 200)); // +200 to print the buttons under the title "Save The King"
			sf::Vector2f toolScale(0.7f, 0.7f);
			m_homeButtonsVec[vec][counter].setOrigin(sf::Vector2f(m_homeButtonsVec[vec][counter].getTexture()->getSize() / 2u));
			m_homeButtonsVec[vec][counter].setPosition(toolLoc);
			m_homeButtonsVec[vec][counter].scale(toolScale);
		}
}

std::vector <sf::Sprite> HomePage::getHomeButtons(int buttonPressed) const
{
	switch (buttonPressed)
	{
	case START_GAME://if the user pressed the start button
		return m_homeButtonsVec[1]; //
	case SHOW_HELP://if the user pressed the help button
		return m_homeButtonsVec[2]; //
	case EXIT_GAME: //if the user pressed the exit button
		return m_homeButtonsVec[3];
	}
	return m_homeButtonsVec[0];
}

// the function builds a Help object 
void HomePage::ShowHelp()
{
	HelpController help((int)m_dimentions.x, (int)m_dimentions.y);
	help.showHelp();
}

//this function handles the clicks on the buttons in the HomePage
bool HomePage::handleButtonsClick(const sf::Vector2f& location)
{
	m_buttonSound.play();
	for (int index = 0; index < BUTTONS; index++)
		if (m_homeButtonsVec[0][index].getGlobalBounds().contains(location))
			switch (index)
			{
			case START_GAME://if the user pressed the start button
				return true;
			case SHOW_HELP://if the user pressed the help button
				ShowHelp(); break;
			case EXIT_GAME: //if the user pressed the exit button
				exit(0);
			}
	return false;
}

//this function handles the case if the mouse is moved on the buttons(it shows other version of the button)
int HomePage::handleMouseMovedOnButtons(sf::Vector2f location)
{
	for (int index = 0; index < BUTTONS; index++)
		if (m_homeButtonsVec[0][index].getGlobalBounds().contains(location))
			switch (index)
			{
			case START_GAME://if the user pressed the start button
				return START_GAME;
			case SHOW_HELP://if the user pressed the help button
				return SHOW_HELP;
			case EXIT_GAME: //if the user pressed the exit button
				return EXIT_GAME;
			}
	return NONE; //case of not moving on buttons
}