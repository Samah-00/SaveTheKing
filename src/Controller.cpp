#include "Controller.h"
#include "Level.h"
#include <fstream>

enum CONST { BUTTONS = 3};

//The constuctor for Controller, takes in the width and height of the window
//we want to create and creates it
Controller::Controller(int width, int height)
    : m_width(width),
    m_height(height),
    m_window(sf::VideoMode(width, height), "Save The King"),
    m_home(width, height),
    m_buttonPressed(3)
{}

//this function operates the game and runs it
//it shows the home page to the game and the menu on the home page
void Controller::operateGame()
{
    //set background
    sf::Texture background;
    background.loadFromFile("Home Page.png");
    auto backgroundImg = sf::Sprite(background);
    m_home.playMusic();

    while (m_window.isOpen())
    {
        m_window.clear();
        m_window.draw(backgroundImg);
        for (int counter = 0; counter < BUTTONS; counter++)
        {
            m_window.draw(m_home.getHomeButtons(m_buttonPressed)[counter]);
        }
        m_window.display();
        if (auto event = sf::Event{}; m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: //if the user closes the window then close the window and exit
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased: //if the user pressed the mouse button
            {
                auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left: //if the button that is pressed is the left button
                    if (m_home.handleButtonsClick(location))//if the start button is pressed then enter the loop
                    {
                        //close the HomePage window
                        m_window.close();
                        m_home.stopMusic();
                        //do the start button
                        Level l;
                        l.levelOperator();
                    }
                    break;
                }
                break;
            }
            case sf::Event::MouseMoved: //if the mouse moved on the window
            {
                auto location = m_window.mapPixelToCoords({ event.mouseMove.x , event.mouseMove.y });
                m_buttonPressed = m_home.handleMouseMovedOnButtons(location);
                break;
            }
            }
        }
    }
}