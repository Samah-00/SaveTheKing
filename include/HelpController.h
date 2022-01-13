#pragma once
#include "Help.h"

class HelpController : public Help
{
public:
	using Help::Help;
	void showHelp();
	void handleHelpEvents(sf::RenderWindow&);
	void handleIconsClick(const sf::Vector2f&, sf::RenderWindow&);
	void showInfo(const std::string info);
	void handleInfoEvents(sf::RenderWindow&);

private:

};