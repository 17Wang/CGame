#include<SFML\Graphics.hpp>
#include"Account.h"
#include<iostream>

bool AccountScreen::show(sf::RenderWindow &renderWindow, int win) {
	//����ͼƬ
	sf::Texture texture;

	renderWindow.setFramerateLimit(240);//����֡������
	int x = 0, y = 0;
	
	if (win==1)
	{
		if (!texture.loadFromFile("./show/win.jpg"))
		{
			std::cout << "����WINʧ��" << std::endl;
			return false;
		}
	}
	else if(win==2)
	{
		if (!texture.loadFromFile("./show/lose.jpg"))
		{
			std::cout << "����LOSEʧ��" << std::endl;
			return false;
		}
	}
	

	//����
	sf::Sprite sprite(texture);

	//����
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("./show/Bernardo Moda.ttf"))
	{
		std::cout << "������ʧ��" << std::endl;
		return false;
	}
	text.setFont(font);
	text.setString("Click your mouse or press any key to continue!");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Bold);
	text.setPosition(350.0f, 700.0f);

	//�����¼�
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

		//=============��һ��
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

		//��ͼ
		renderWindow.display();
	}
}