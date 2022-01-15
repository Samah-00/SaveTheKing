#include "HelpController.h"


// this function creates and opens the Help window and prints to it
// the elements of m_helpText and the elements of m_icons.
// the window is opened in waitEvent mode, when the user clicks on one of the icons,
// an Info window is opened to show more info about that icon.
void HelpController::showHelp()
{
    sf::RenderWindow helpWindow(sf::VideoMode(m_width, m_hight), "Help");
    auto backgroundImg = sf::Sprite(m_background);  // set a background image for helpWindow
    while (helpWindow.isOpen())
    {
        helpWindow.clear();
        helpWindow.draw(backgroundImg);
        for (int index = 0; index < m_helpText.size(); index++)//draw the text
            helpWindow.draw(m_helpText[index]);

        for (int index = 0; index < m_iconsVec.size(); index++)//draw the icons
            helpWindow.draw(m_iconsVec[index]);
        helpWindow.draw(m_backButton);
        helpWindow.display();
        handleHelpEvents(helpWindow);
    }
}

// The showHelp function calls this function in a while loop to handle the events in the helpWindow.
void HelpController::handleHelpEvents(sf::RenderWindow& helpWindow)
{
    sf::Vector2f location;
    if (auto event = sf::Event{}; helpWindow.waitEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            helpWindow.close(); break;

        case sf::Event::MouseButtonReleased: //if the user pressed the mouse button
            location = helpWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            handleIconsClick(location, helpWindow);
            break;
        case sf::Event::MouseMoved: //if the user moved the mouse on the window
        {
            location = helpWindow.mapPixelToCoords({ event.mouseMove.x , event.mouseMove.y });
            if (m_backButton.getGlobalBounds().contains(location))
                m_backButton.setTexture(m_backClickedTex);
            else
                m_backButton.setTexture(m_backTex);
            break;
        }
        default:
            break;
        }
}

// this function handles the clicks on the characters' icons.
// it desides which character info to send to the showInfo function. 
void HelpController::handleIconsClick(const sf::Vector2f& location, sf::RenderWindow& window)
{
    m_iconClickedSound.play();
    if (m_backButton.getGlobalBounds().contains(location))
    {
        window.close(); return;
    }

    std::string info;
    for (int index = 0; index < NUM_OF_ICONS; index++)
        if (m_iconsVec[index].getGlobalBounds().contains(location))
            switch (index)
            {
            case KINGICON: // king icon is pressed
                info = "King"; break;
            case MAGEICON: // mage icon is pressed
                info = "Mage"; break;
            case WARRIORICON: // warrior icon is pressed
                info = "Warrior"; break;
            case THIEFICON: // theif icon is pressed 
                info = "Thief"; break;
            case ENEMYICON: // enemy icon is pressed 
                info = "Enemy"; break;
            }
    showInfo(info);
}

// this function opens a window (in waitEvent mode) when clicking on a character in Help window.
// It shows more information about that character.
void HelpController::showInfo(const std::string info)
{
    std::vector <sf::Text> info_vec = fillTextVec(info); // read info about the character from a txt file to a vector
    auto backgroundImg = sf::Sprite(m_background);     // set background for infoWindow
    sf::RenderWindow infoWindow(sf::VideoMode(m_width, m_hight), info);

    while (infoWindow.isOpen())
    {
        infoWindow.clear();
        infoWindow.draw(backgroundImg);
        infoWindow.draw(m_backButton);
        for (int index = 0; index < info_vec.size(); index++)
            infoWindow.draw(info_vec[index]);
        infoWindow.display();
        handleInfoEvents(infoWindow);
    }
}

// The showInfo function calls this function in a while loop to handle the events in the infoWindow.
void HelpController::handleInfoEvents(sf::RenderWindow& infoWindow)
{
    if (auto event = sf::Event{}; infoWindow.waitEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            infoWindow.close(); break;

        case sf::Event::MouseMoved:
        {
            auto location = infoWindow.mapPixelToCoords({ event.mouseMove.x , event.mouseMove.y });
            if (m_backButton.getGlobalBounds().contains(location))
                m_backButton.setTexture(m_backClickedTex);
            else
                m_backButton.setTexture(m_backTex);
            break;
        }
        case sf::Event::MouseButtonReleased: //if the user pressed the mouse button
            auto location = infoWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            if (m_backButton.getGlobalBounds().contains(location))
            {
                m_iconClickedSound.play();
                infoWindow.close();
                return;
            }
            break;
        }
}