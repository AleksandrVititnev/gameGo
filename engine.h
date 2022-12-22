#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include "idNode.h"
#include "gameField.h"
#include "gameLogic.h"
#include "compLogic.h"
#include "additionalFunctions.h"
class engine
{
private:
	sf::RenderWindow window;

	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;
	sf::Font font;
	sf::Text textWin;
	
	gameField* field;
	gameLogic* rule;
	compLogic* AI;
	id_node* turn;
	id_node* aiTurn;

	bool showTerr;
	bool aiOn;
	bool secret;

	bool passFirst;
	bool passSecond;
	bool end;
public:
	engine(sf::String _file, sf::String _fileFont);

	void start();
	void comp_turn(bool& _wasTurn);
};

