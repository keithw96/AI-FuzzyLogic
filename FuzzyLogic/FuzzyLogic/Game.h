#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "FuzzyLogic.h"
#include "FuzzyMembership.h"
class Game
{
public:
	Game();
	~Game();

	void init();
	void update();
	void pollEvent();
	void fuzzyLogic();
	void render();
private:
	sf::RenderWindow m_window;

	sf::Font m_font;

	sf::Sprite m_allySprite;
	sf::Sprite m_alienSprite;
	sf::Texture m_allyTxt;
	sf::Texture m_alienTxt;

	sf::Text m_allyText;
	sf::Text m_alienText;
	sf::Text m_distanceText;
	sf::Text m_pressSpaceText;
	sf::Text m_VersusText;
};

