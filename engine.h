#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include "idNode.h"
#include "gameField.h"
#include "gameLogic.h"
#include "compLogic.h"
class engine
{
private:
	sf::RenderWindow window;

	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;
	
	gameField* field;
	gameLogic* rule;
	compLogic* AI;
	id_node* turn;

public:
	engine(sf::String _file);

	void start();
};

