#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\Audio.hpp>
#include"Game.h"
#include"Splash.h"
#include"Account.h"
#include"Menu.h"
#include"VisibleGameObject.h"
#include<iostream>
using namespace std;

sf::RenderWindow Game::_mainWindow;
sf::Clock Game::_clock;
int Game::count = 0;
float Game::SCREEN_WIDTH = 1280;
float Game::SCREEN_HEIGHT = 800;

Game::Game(){
	settings.antialiasingLevel = 8;
	_gameState = Game::Uninitialized;
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "G.O.",sf::Style::Default,settings);

	if (!_music1.openFromFile("./music/BGM12.wav"))
	{
		std::cout << "打开BGM12失败" << std::endl;
	}
	_music1.play();
	_music1.setLoop(true);

	if (!_music2.openFromFile("./music/BGM3.wav"))
	{
		std::cout << "打开BGM3失败" << std::endl;
	}
	_music2.setLoop(true);
	_music2.setVolume(50);

	_WIN = 0;
}

void Game::Start() {
	if (_gameState != Game::Uninitialized) 
		return;

	_gameState = Game::ShowingSplash;
	load_all();
	_gameMap.Load("./show/2.jpg");
	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting() {
	if (_gameState == Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::GetWindow(){
	return _mainWindow;
}


void Game::GameLoop() {
	switch (_gameState)
	{
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		
		break;
	}
	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}
	case Game::Playing:
	{
		_music1.stop();
		if (_music2.getStatus()!=_music2.Playing)
		{
			_music2.play();
		}
		_mainWindow.setFramerateLimit(30);
		sf::Event event;
		while (_mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_gameState = Game::Exiting;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) ShowMenu();
			}
			break;
		}

		_mainWindow.clear(sf::Color::White);
		//=========draw something

		Logic();

		//=======================

		_mainWindow.display();
		break;
	}
	case Game::Account:
	{
		ShowAccount();
		break;
	}
	}
}

void Game::ShowSplashScreen() {
	SplashScreen splashScreen;
	if (splashScreen.show(_mainWindow))
	{
		_gameState = Game::ShowingMenu;
		return;
	}
}
void Game::ShowMenu() {
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}
void Game::ShowAccount() {
	AccountScreen account;
	if (account.show(_mainWindow,_WIN))
	{
		_gameState = Game::Exiting;
		return;
	}
}

void Game::load_all() {
	_player1.Load("./bin/寒冰1.png");//***
	_player1.SetPosition((1024 / 2) - 45, 650);//***
	_player1.SetSize(0.7f, 0.7f, true);
	//_player1.SetOrigin();

	_enemy1.Load("./bin/石头_正面.png");//***
	_enemy1.SetPosition((1024 / 2) - 45, 300);//***
	_enemy1.SetSize(0.6f, 0.6f, true);
	//_enemy1.SetOrigin();

	_bullet1.Load("./bin/弓箭2.png");//玩家
	_bullet1.SetSize(0.5f, 0.5f, true);
	//_bullet1.SetOrigin();
	
	_bullet2.Load("./bin/火球2.png");//BOSS
	_bullet2.SetSize(0.3f, 0.3f, true);
	_bullet2.Set_velocity(20);
	//_bullet2.SetOrigin();

	_bullet3.Load("./bin/弓箭3.png");//玩家
	_bullet3.SetSize(0.5, 0.5, true);

	if (_player1.get_Hp() <= 0.0f)
	{

	}
}

void Game::Logic() {
	_gameMap.Draw(_mainWindow);
	_player1.Update();
	_player1.skill_1(_bullet1);
	_player1.skill_2();
	_enemy1.Update(_player1);
	_enemy1.skill_3();

	_player1.Draw(_mainWindow);
	_enemy1.Draw(_mainWindow);

	if_fire();//子弹类

	static int index = 0;
	if (_player1.get_Hp()<=0.0f) {
		_enemy1.can_move = false;
		_WIN = 2;
		index++;
		if (index >= 30)
		{
			_gameState = Account;
		}
	}

	if (_enemy1.get_Hp() <= 0.0f) {
		_enemy1.can_move = false;
		index++;
		_WIN = 1;
		if (index >= 30)
		{
			_gameState = Account;
		}
	}
}


//================子弹处理
void Game::if_fire() {
	_bullet1.Update(_player1,_enemy1);
	_bullet1.Draw(_mainWindow);

	if (!Bullet::I_enemy)
	{
		_bullet2.Update_Boss(_enemy1, _player1);
		_bullet2.Draw(_mainWindow);
	}

	_bullet3.Update_I(_player1, _enemy1);
	_bullet3.Draw(_mainWindow);

	/*if (count == 0||_bullet1.if_Space)
	{
		_bullet1.Update(_player1);
		_bullet1.Draw(_mainWindow);
	}
	if (_bullet1.if_Space&&count == 0)
	{
		count += 1;
	}
	if(!_bullet1.if_Space&&count==1)
	{
		count -= 1;
	}
	if (count == 1 || _bullet2.if_Space)
	{
		_bullet2.Update(_player1);
		_bullet2.Draw(_mainWindow);
	}*/
}


