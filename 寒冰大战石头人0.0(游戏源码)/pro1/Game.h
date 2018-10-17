#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\Audio.hpp>
#include"VisibleGameObject.h"
#include"GameMap.h"

#ifndef GAME
#define GAME
class Game
{
public:
	Game();
	void Start();
	static sf::RenderWindow &GetWindow();

	static float SCREEN_WIDTH;
	static float SCREEN_HEIGHT;

private:
	bool IsExiting();
	void GameLoop();
	
	void ShowSplashScreen();
	void ShowMenu();
	void ShowAccount();

	void load_all();
	void Logic();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting, Account
	};

	static sf::RenderWindow _mainWindow;
	sf::ContextSettings settings;
	static sf::Clock _clock;
	sf::Music _music1;

	sf::Music _music2;

	GameState _gameState;

	//=============成员
	Player _player1;
	Enemy _enemy1;
	Bullet _bullet1;
	Bullet _bullet2;
	Bullet _bullet3;
	//Bullet _bullet4;

	//===========子弹的特殊处理
	void if_fire();
	static int count;

	//===========地图
	GameMap _gameMap;

	int _WIN;
};

#endif