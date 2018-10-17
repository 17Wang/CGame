#include<SFML\Graphics.hpp>
#include<iostream>
#include"GameObjectManager.h"
#include"Game.h"

std::map<std::string, VisibleGameObject*> GameObjectManager::_gameObjects;

GameObjectManager::GameObjectManager() {

}

GameObjectManager::~GameObjectManager() {
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject*gameObject) {
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name){
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;//释放指针指向的内存空间
		_gameObjects.erase(results);
	}
}

VisibleGameObject *GameObjectManager::Get(std::string name) {
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;
}

int GameObjectManager::GetObjectCount() {
	return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow &renderWindow) {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll() {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		itr->second->Update();
		itr++;
	}
}
