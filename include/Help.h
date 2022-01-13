#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>

enum CONSTS { NUM_OF_ICONS = 5, CHAR_SIZE = 30 };
enum Icons { KINGICON, MAGEICON, WARRIORICON, THIEFICON, ENEMYICON };

class Help
{
public:
	Help(int width, int hight);

protected:
	std::vector<sf::Sprite> m_iconsVec;
	std::vector <sf::Texture> m_textures;
	std::vector<sf::Text> m_helpText;
	sf::Texture m_background;
	sf::Texture m_backTex;
	sf::Texture m_backClickedTex;
	sf::Sprite m_backButton;
	sf::SoundBuffer m_iconClickedBuf;
	sf::Sound m_iconClickedSound;
	sf::Font m_font;
	int m_width;
	int m_hight;

	// helper functions:
	std::vector <sf::Text> fillTextVec(const std::string fileName);
	void fillIconsVec();
	void createBackButton();
};