#include"SFML\Graphics.hpp"
#include"GameMap.h"
#include<iostream>

void GameMap::Load(std::string filename)
{
	if (_texture.loadFromFile(filename) == false)
	{
		std::cout << "´ò¿ªplayerÊ§°Ü" << std::endl;
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void GameMap::Draw(sf::RenderWindow &rw) {
	if (_isLoaded)
	{
		rw.draw(_sprite);
	}
}

void GameMap::Update() {

}

