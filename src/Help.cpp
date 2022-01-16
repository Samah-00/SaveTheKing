#include "Help.h"

// the c-tor reseives the dimentions of the Help window 
// It inializes the elemnts of the vector m_icons, the elements of vector m_helpText, the textures and sounds.
Help::Help(int width, int hight) :
    m_width(width),
    m_hight(hight)
{
    m_font.loadFromFile("C:/Windows/Fonts/CASTELAR.ttf");
    m_background.loadFromFile("Background.png");
    m_textures.resize(NUM_OF_ICONS);
    m_textures[KINGICON].loadFromFile("King.png");
    m_textures[MAGEICON].loadFromFile("Mage.png");
    m_textures[WARRIORICON].loadFromFile("Warrior.png");
    m_textures[THIEFICON].loadFromFile("Thief.png");
    m_textures[ENEMYICON].loadFromFile("Enemy.png");
    m_backTex.loadFromFile("Back Button.png");
    m_backClickedTex.loadFromFile("Back Button Clicked.png");
    m_iconClickedBuf.loadFromFile("ButtonClickedSound.wav");
    m_iconClickedSound = sf::Sound(m_iconClickedBuf);
    m_helpText = fillTextVec("Help");
    fillIconsVec();
    createBackButton();
}

// helper function, it copies a txt file to a sf::Text vector.
std::vector <sf::Text> Help::fillTextVec(const std::string fileName)
{
    std::ifstream data_file;
    std::string line;
    std::vector <sf::Text> text_vec;

    data_file.open(fileName + ".txt");
    while (!data_file.eof()) {
        getline(data_file, line);
        text_vec.push_back(sf::Text(line, m_font));
    }
    //preparing the text to be printied on the screen
    for (int index = 0; index < text_vec.size(); index++) {
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
    auto kingImg = sf::Sprite(m_textures[KINGICON]);
    m_iconsVec.push_back(kingImg);
    auto mageImg = sf::Sprite(m_textures[MAGEICON]);
    m_iconsVec.push_back(mageImg);
    auto warriorImg = sf::Sprite(m_textures[WARRIORICON]);
    m_iconsVec.push_back(warriorImg);
    auto thiefImg = sf::Sprite(m_textures[THIEFICON]);
    m_iconsVec.push_back(thiefImg);
    auto enemyImg = sf::Sprite(m_textures[ENEMYICON]);
    m_iconsVec.push_back(enemyImg);

    //preparing the characters' icons to be printied on the screen
    for (int counter = 0; counter < m_iconsVec.size(); counter++) {
        sf::Vector2f iconLoc(float((m_width / NUM_OF_ICONS) * counter), float(CHAR_SIZE * (m_helpText.size() + 2))); //CHAR_WIDTH * m_helpText.size() to print the images under the text
        sf::Vector2f iconScale(0.3f, 0.3f);
        m_iconsVec[counter].setPosition(iconLoc);
        m_iconsVec[counter].scale(iconScale);
    }
}

// Helper function for the c-tor, it creates the back button of help and info windows
void Help::createBackButton()
{
    m_backButton.setTexture(m_backTex);
    sf::Vector2f backLoc(float(m_width / 2.7), float(CHAR_SIZE * (m_helpText.size() + 2) + m_iconsVec[0].getGlobalBounds().height)); //CHAR_WIDTH * m_helpText.size() to print the images under the text
    sf::Vector2f backScale(0.3f, 0.3f);
    m_backButton.setPosition(backLoc);
    m_backButton.scale(backScale);
}