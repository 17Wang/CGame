#pragma once
#include<SFML\Graphics.hpp>
#include<list>

#ifndef MAINMENU
#define MAINMENU

class MainMenu
{
public:
	enum MenuResult {Nothing,Exit,Play};

	struct MenuItem
	{
		sf::Text text;
		sf::Font font;
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::Event &event);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};

#endif // !MAINMENU

