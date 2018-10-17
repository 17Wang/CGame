#include<SFML\Graphics.hpp>
#include"Menu.h"
#include<iostream>

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window) {
	sf::Texture texture;
	if (!texture.loadFromFile("./show/MainMenu.jpg"))
	{
		std::cout << "打开MainMenu图片失败" << std::endl;
		return MenuResult::Exit;
	}

	sf::Sprite sprite(texture);

	//主菜单中的开始游戏按钮
	MenuItem playButton;
	if (!playButton.font.loadFromFile("./show/politicaregular.ttf"))
	{
		std::cout << "打开字体失败" << std::endl;
		return MainMenu::Exit;
	}
	playButton.text.setFont(playButton.font);
	playButton.text.setString("play");
	playButton.text.setFillColor(sf::Color::White);
	playButton.text.setCharacterSize(30);
	playButton.text.setStyle(sf::Text::Bold);
	playButton.text.setPosition(250.0f, 300.0f);

	playButton.rect.left = 248;
	playButton.rect.top = 305;
	playButton.rect.width = 47;
	playButton.rect.height = 32;

	playButton.action = Play;

	//主菜单中的退出游戏按钮
	MenuItem exitButton;
	if (!exitButton.font.loadFromFile("./show/politicaregular.ttf"))
	{
		std::cout << "打开字体失败" << std::endl;
		return MainMenu::Exit;
	}
	exitButton.text.setFont(exitButton.font);
	exitButton.text.setString("exit");
	exitButton.text.setFillColor(sf::Color::White);
	exitButton.text.setCharacterSize(30);
	exitButton.text.setStyle(sf::Text::Bold);
	exitButton.text.setPosition(250.0f, 400.0f);

	exitButton.rect.left = 248;
	exitButton.rect.top = 405;
	exitButton.rect.width = 47;
	exitButton.rect.height = 32;

	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	//===============================================
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			MenuResult result = GetMenuResponse(event);
			switch (result)
			{
			case MainMenu::Play:
				return MainMenu::Play;
				break;
			case MainMenu::Exit:
				return MainMenu::Exit;
			case MainMenu::Nothing:
				break;
			}
		}

		//================================================== 按 钮 颜 色
		//==============对 play 按钮
		int x = event.mouseMove.x, y = event.mouseMove.y;
		if (x > playButton.rect.left
			&&x<playButton.rect.width + playButton.rect.left
			&&y>playButton.rect.top
			&&y < playButton.rect.height + playButton.rect.top)
		{
			playButton.text.setFillColor(sf::Color::Red);
		}
		else
		{
			playButton.text.setFillColor(sf::Color::White);
		}
		//==============对 exit 按钮
		if (x > exitButton.rect.left
			&&x<exitButton.rect.width + exitButton.rect.left
			&&y>exitButton.rect.top
			&&y < exitButton.rect.height + exitButton.rect.top)
		{
			exitButton.text.setFillColor(sf::Color::Red);
		}
		else
		{
			exitButton.text.setFillColor(sf::Color::White);
		}
		//==================================================

		window.clear(sf::Color::Black);

		//draw something
		window.draw(sprite);
		window.draw(playButton.text);
		window.draw(exitButton.text);

		window.display();
	}
	//=============================================
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;
	
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = it->rect;
		if (x > menuItemRect.left
			&&x<(menuItemRect.left + menuItemRect.width)
			&& y>menuItemRect.top
			&&y < (menuItemRect.top + menuItemRect.height))
		{
			return it->action;
		}
	}

	return Nothing;
}


MainMenu::MenuResult MainMenu::GetMenuResponse(sf::Event &event) {
	//_judgeRed(event.mouseButton.x, event.mouseButton.y,window);
	if (event.type == sf::Event::MouseButtonPressed)
	{
		return HandleClick(event.mouseButton.x, event.mouseButton.y);
	}
	if (event.type == sf::Event::Closed)
	{
		return Exit;
	}
}


