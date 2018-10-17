#include<SFML\Graphics.hpp>
#include"Account.h"
#include<iostream>

bool AccountScreen::show(sf::RenderWindow &renderWindow, int win) {
	//背景图片
	sf::Texture texture;

	renderWindow.setFramerateLimit(240);//设置帧率限制
	int x = 0, y = 0;
	
	if (win==1)
	{
		if (!texture.loadFromFile("./show/win.jpg"))
		{
			std::cout << "加载WIN失败" << std::endl;
			return false;
		}
	}
	else if(win==2)
	{
		if (!texture.loadFromFile("./show/lose.jpg"))
		{
			std::cout << "加载LOSE失败" << std::endl;
			return false;
		}
	}
	

	//精灵
	sf::Sprite sprite(texture);

	//文字
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("./show/Bernardo Moda.ttf"))
	{
		std::cout << "打开字体失败" << std::endl;
		return false;
	}
	text.setFont(font);
	text.setString("Click your mouse or press any key to continue!");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Bold);
	text.setPosition(350.0f, 700.0f);

	//创建事件
	while (renderWindow.isOpen())
	{
		static int index = 0;
		index++;
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (index > 240)
			{
				if (event.type == sf::Event::EventType::KeyPressed
					|| event.type == sf::Event::EventType::MouseButtonPressed)
				{
					return true;
				}
			}
			
			if (event.type == sf::Event::EventType::Closed)
			{
				renderWindow.close();
				exit(0);
			}
		}

		renderWindow.clear(sf::Color::Black);

		//=============闪一闪
		if (x <= 255 && y == 0)
		{
			x++;
		}
		if (x == 255)
		{
			y = x;
		}
		if (y != 0)
		{
			x--; y--;
		}
		//std::cout << x << std::endl;
		text.setFillColor(sf::Color(0,0, 0, x));

		renderWindow.clear(sf::Color::White);

		renderWindow.draw(sprite);
		if(index>=240)
			renderWindow.draw(text);

		//绘图
		renderWindow.display();
	}
}