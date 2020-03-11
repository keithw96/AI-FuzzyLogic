#include "Game.h"

Game::Game() : m_window(sf::VideoMode(1920,1080), "Fuzzy Logic", sf::Style::Fullscreen)
{
	//Prevent Double trigger on keyReleased event
	m_window.setKeyRepeatEnabled(false);
	
	if (!m_font.loadFromFile("./Resources/Fonts/Oswald-Bold.ttf"))
	{
		std::cout << "Could not load font" << std::endl;
	}

	if (!m_allyTxt.loadFromFile("./Resources/Sprites/Ally.png"))
	{
		std::cout << "Could not load Ally Texture" << std::endl;
	}

	if (!m_alienTxt.loadFromFile("./Resources/Sprites/Alien.png"))
	{
		std::cout << "Could not load Ally Texture" << std::endl;
	}

	m_allyTxt.setSmooth(true);
	m_allySprite.setTexture(m_allyTxt);
	m_allySprite.setPosition((m_window.getSize().x / 2) - (m_allySprite.getTextureRect().width / 2), m_window.getSize().y - (m_allySprite.getTextureRect().height));
	
	m_alienTxt.setSmooth(true);
	m_alienSprite.setTexture(m_alienTxt);
	m_alienSprite.setPosition((m_window.getSize().x / 2) - (m_alienSprite.getTextureRect().width / 2), 50);

	m_allyText.setFont(m_font);
	m_allyText.setString("Number of Allies: 0");
	m_allyText.setFillColor(sf::Color::Red);
	m_allyText.setCharacterSize(60);
	m_allyText.setPosition(sf::Vector2f(1220, 880));

	m_alienText.setFont(m_font);
	m_alienText.setString("Number of Aliens: 0");
	m_alienText.setFillColor(sf::Color::Red);
	m_alienText.setCharacterSize(60);
	m_alienText.setPosition(sf::Vector2f(100, 100));

	m_distanceText.setFont(m_font);
	m_distanceText.setString("The Aliens are 0m away!");
	m_distanceText.setFillColor(sf::Color::Red);
	m_distanceText.setCharacterSize(60);
	m_distanceText.setPosition(sf::Vector2f(1200, 100));

	m_pressSpaceText.setFont(m_font);
	m_pressSpaceText.setString("Press Space To Generate A Battle!");
	m_pressSpaceText.setFillColor(sf::Color::Red);
	m_pressSpaceText.setCharacterSize(45);
	m_pressSpaceText.setPosition(sf::Vector2f(150, 880));

	m_VersusText.setFont(m_font);
	m_VersusText.setString("VS");
	m_VersusText.setCharacterSize(150);
	m_VersusText.setFillColor(sf::Color::Red);
	m_VersusText.setPosition(900, 400);
}

Game::~Game()
{
}

void Game::init()
{
	srand(time(NULL));
}

void Game::update()
{
	while (m_window.isOpen())
	{
		pollEvent();

		render();
	}
}

void Game::pollEvent()
{
	sf::Event event;
	
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Space)
			{
				fuzzyLogic();
			}
		default:
			break;
		}
	}
}

void Game::fuzzyLogic()
{
	//Variables
	int noOfAliens = std::rand() % 51 + 5;
	m_alienText.setString("Number of Aliens: " + std::to_string(noOfAliens));

	int distance = std::rand() % 101 + 30;
	m_distanceText.setString("The Aliens are " + std::to_string(distance) + "m away!");

	std::cout << "Alien Fleet Numbers " << noOfAliens << " ships \nThey are " << distance << " meters away!" << std::endl;

	//Size Assesment 
	double mTiny = FuzzyMembership::FuzzyTriangle(noOfAliens, 0.0, 10.0);
	double mSmall = FuzzyMembership::FuzzyTrapezoid(noOfAliens, 2.0, 10.0, 15.0, 20.0);
	double mModerate = FuzzyMembership::FuzzyTrapezoid(noOfAliens, 15.0, 20.0, 25.0, 30.0);
	double mLarge = FuzzyMembership::FuzzyGrade(noOfAliens, 25.0, 30.0);

	//Distance away from allies
	double mClose = FuzzyMembership::FuzzyTriangle(distance, 0.0, 30.0);
	double mMedium = FuzzyMembership::FuzzyTrapezoid(distance, 10.0, 30.0, 50.0, 70.0);
	double mFar = FuzzyMembership::FuzzyGrade(distance, 50.0, 70.0);

	//Threat Level
	double lowThreat = FuzzyLogic::FuzzyOR(FuzzyLogic::FuzzyAND(mMedium, mTiny),FuzzyLogic::FuzzyAND(mMedium, mSmall)	);
	lowThreat = FuzzyLogic::FuzzyOR(lowThreat, FuzzyLogic::FuzzyAND(mFar, FuzzyLogic::FuzzyNOT(mLarge))	);

	double mediumThreat = FuzzyLogic::FuzzyOR(FuzzyLogic::FuzzyAND(mClose, mTiny), FuzzyLogic::FuzzyAND(mMedium, mModerate));
	mediumThreat = FuzzyLogic::FuzzyOR(mediumThreat, FuzzyLogic::FuzzyAND(mFar, mLarge));

	double highThreat = FuzzyLogic::FuzzyOR(FuzzyLogic::FuzzyAND(mClose, FuzzyLogic::FuzzyNOT(mTiny)),FuzzyLogic::FuzzyAND(mLarge, mMedium));

	//Deploy
	int numberToDeploy = (lowThreat * 3 + mediumThreat * 30 + highThreat * 50) / (lowThreat + mediumThreat + highThreat);
	m_allyText.setString("Number of Allies: " + std::to_string(numberToDeploy));
	std::cout << "number of units to deploy is: " << numberToDeploy << std::endl;

}

void Game::render()
{
	m_window.clear();
	m_window.draw(m_allySprite);
	m_window.draw(m_alienSprite);
	m_window.draw(m_VersusText);
	m_window.draw(m_pressSpaceText);
	m_window.draw(m_allyText);
	m_window.draw(m_alienText);
	m_window.draw(m_distanceText);
	m_window.display();
}
