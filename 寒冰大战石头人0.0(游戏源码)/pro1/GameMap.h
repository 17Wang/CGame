#pragma once
#include"SFML\Graphics.hpp"
#include<iostream>


#ifndef GAMEMAP
#define GAMEMAP

class GameMap
{
public:
	void Load(std::string filename);
	void Draw(sf::RenderWindow &window);
	void Update();
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
};

#endif // !GAMEMAP

