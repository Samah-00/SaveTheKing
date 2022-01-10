#include "Help.h"

enum CONSTS { NUM_OF_ICONS = 4, CHAR_SIZE = 30 };
enum Icons { KING, MAGE, WARRIOR, THIEF, ExtraTimeGift, LessTimeGift, KillGift};

// the c-tor reseives the dimentions of the Help window 
// It inializes the elemnts of the vector m_icons, the elements of vector m_helpText, the textures and sounds.
Help::Help(int width, int hight) :
    m_width(width),
    m_hight(hight)
{
    m_font.loadFromFile("C:/Windows/Fonts/CASTELAR.ttf");
    m_background.loadFromFile("Background.png");
    m_textures.resize(NUM_OF_ICONS);
    m_textures[KING].loadFromFile("King.png");
    m_textures[MAGE].loadFromFile("Mage.png");
    m_textures[WARRIOR].loadFromFile("Warrior.png");
    m_textures[THIEF].loadFromFile("Thief.png");
    m_backTex.loadFromFile("Back Button.png");
    m_backClickedTex.loadFromFile("Back Button Clicked.png");
    m_iconClickedBuf.loadFromFile("ButtonClickedSound.wav");
    m_iconClickedSound = sf::Sound(m_iconClickedBuf);
    m_helpText = fillTextVec("Help");
    fillIconsVec();
}

// this function creates and opens the Help window and prints to it
// the elements of m_helpText and the elements of m_icons.
// the window is opened in waitEvent mode, when the user clicks on one of the icons,
// an Info window is opened to show more info about that icon.
void Help::showHelp()
{
    sf::RenderWindow helpWindow(sf::VideoMode(m_width, m_hight), "Help");
    auto backgroundImg = sf::Sprite(m_background);  // set a background image for helpWindow
    sf::Vector2f location;
    while (helpWindow.isOpen())
    {
        helpWindow.clear();
        helpWindow.draw(backgroundImg);
        for (int index = 0; index < m_helpText.size(); index++)
            helpWindow.draw(m_helpText[index]);

        for (int index = 0; index < m_iconsVec.size(); index++)
            helpWindow.draw(m_iconsVec[index]);
        helpWindow.draw(m_backButton);
        helpWindow.display();

        if (auto event = sf::Event{}; helpWindow.waitEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                helpWindow.close();
                break;

            case sf::Event::MouseButtonReleased: //if the user pressed the mouse button
                location = helpWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                handleIconsClick(location, helpWindow);
                break;
            case sf::Event::MouseMoved:
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
}

// helper function, it copies a txt file to a sf::Text vector.
std::vector <sf::Text> Help::fillTextVec(const std::string fileName)
{
    std::ifstream data_file;
    std::string line;
    std::vector <sf::Text> text_vec;

    data_file.open(fileName + ".txt");
    while (!data_file.eof())
    {
        getline(data_file, line);
        text_vec.push_back(sf::Text(line, m_font));
    }
    for (int index = 0; index < text_vec.size(); index++)
    {
        sf::Vector2f linePos(float(0), float(CHAR_SIZE * index));
        text_vec[index].setPosition(linePos);
        text_vec[index].setCharacterSize(25);
        text_vec[index].setOutlineColor(sf::Color::Black);
        if(index == text_vec.size() - 1 && fileName == "Help")
            text_vec[index].setOutlineColor(sf::Color::Red);
        text_vec[index].setOutlineThickness(1.f);
    }
    data_file.close();
    return text_vec;
}

// helper function for the c-tor, it creates the elements of m_icons which is a vector of
// sf::Sprite elements that represent characters in the game.
void Help::fillIconsVec()
{
    auto kingImg = sf::Sprite(m_textures[KING]);
    m_iconsVec.push_back(kingImg);
    auto mageImg = sf::Sprite(m_textures[MAGE]);
    m_iconsVec.push_back(mageImg);
    auto warriorImg = sf::Sprite(m_textures[WARRIOR]);
    m_iconsVec.push_back(warriorImg);
    auto thiefImg = sf::Sprite(m_textures[THIEF]);
    m_iconsVec.push_back(thiefImg);
    m_backButton.setTexture(m_backTex); // sprite back button

    for (int counter = 0; counter < m_iconsVec.size(); counter++)
    {
        sf::Vector2f iconLoc(float((m_width / NUM_OF_ICONS) * counter), float(CHAR_SIZE * (m_helpText.size() + 2))); //CHAR_WIDTH * m_helpText.size() to print the images under the text
        sf::Vector2f iconScale(0.3f, 0.3f);
        m_iconsVec[counter].setPosition(iconLoc);
        m_iconsVec[counter].scale(iconScale);
    }
    sf::Vector2f backLoc(float(m_width / 2.7), float(CHAR_SIZE * (m_helpText.size() + 2) + m_iconsVec[0].getGlobalBounds().height)); //CHAR_WIDTH * m_helpText.size() to print the images under the text
    sf::Vector2f backScale(0.3f, 0.3f);
    m_backButton.setPosition(backLoc);
    m_backButton.scale(backScale);
}

// this function handles the clicks on the characters' icons.
// it desides which character info to send to the showInfo function. 
void Help::handleIconsClick(const sf::Vector2f& location, sf::RenderWindow& window)
{
    m_iconClickedSound.play();
    if (m_backButton.getGlobalBounds().contains(location))
    {
        window.close();
        return;
    }

    std::string info;
    for (int index = 0; index < NUM_OF_ICONS; index++)
    {
        if (m_iconsVec[index].getGlobalBounds().contains(location))
            switch (index)
            {
            case KING: // king icon is pressed
                info = "King";
                break;
            case MAGE: // mage icon is pressed
                info = "Mage";
                break;
            case WARRIOR: // warrior icon is pressed
                info = "Warrior";
                break;
            case THIEF: // theif icon is pressed 
                info = "Thief";
                break;
            case ExtraTimeGift:
                info = "Increase time gift";
                break;
            case LessTimeGift:
                info = "Decrease time gift";
                break;
            case KillGift:
                info = "Kill enemy gift";
                break;
            }
    }
    showInfo(info);
}

// this function opens a window (in waitEvent mode) when clicking on a character in Help window.
// It shows more information about that character.
void Help::showInfo(const std::string info)
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

        if (auto event = sf::Event{}; infoWindow.waitEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                infoWindow.close(); break;

            case sf::Event::MouseMoved:
            {
                auto location = infoWindow.mapPixelToCoords({ event.mouseMove.x , event.mouseMove.y });
                if(m_backButton.getGlobalBounds().contains(location))
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
}