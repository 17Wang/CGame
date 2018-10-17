#include<SFML\Graphics.hpp>
#include"Splash.h"
#include<iostream>

bool SplashScreen::show(sf::RenderWindow &renderWindow) {
	//����ͼƬ
	sf::Texture texture;

	renderWindow.setFramerateLimit(240);//����֡������
	int x = 0, y = 0;

	if (!texture.loadFromFile("./show/splash.jpg"))
	{
		std::cout << "����Splashʧ��" << std::endl;
		return false;
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

	sf::Text title;
	sf::Font font1;
	if (!font1.loadFromFile("./show/����Ӳ������.ttf"))
	{
		std::cout << "������ʧ��" << std::endl;
		return false;
	}
	title.setFont(font1);
	title.setString(L"���������ϵ��һ��֮��");
	title.setFillColor(sf::Color(255,255,255,180));
	title.setCharacterSize(60);
	title.setStyle(sf::Text::Bold);
	title.setPosition(100.0f,150.0f);	
	//�����¼�
	while (renderWindow.isOpen())
	{
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed)
			{
				return true;
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
		text.setFillColor(sf::Color(255, 255, 255, x));

		renderWindow.clear(sf::Color::White);

		renderWindow.draw(sprite);
		renderWindow.draw(title);
		renderWindow.draw(text);

		//��ͼ
		renderWindow.display();
	}
}