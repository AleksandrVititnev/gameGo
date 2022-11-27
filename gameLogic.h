//File contain game logic, game rules.
#pragma once
#include <stdexcept>
#include "gameField.h"
#include "additionalFunctions.h"
#include "idNode.h"

class gameLogic
{
private:

public:
	gameLogic() { }

	bool can_make_turn(gameField* _field, id_node* _node, char _who);
	void apply_turn(gameField* _field, id_node* _node);

	~gameLogic() { }
};

