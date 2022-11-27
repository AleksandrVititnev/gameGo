//File contains computer logic.
#pragma once
#include <stdexcept>
#include "additionalFunctions.h"
#include "gameField.h"
#include "gameLogic.h"
#include "idNode.h"

class compLogic
{
private:
	gameLogic* rules;

	int max(int _what, int _with) {
		return _what > _with ? _what : _with;
	}
	int min(int _what, int _with) {
		return _what < _with ? _what : _with;
	}
public:
	compLogic() : rules(nullptr) {
		rules = new gameLogic();
	}

	id_node* get_next_turn(gameField* _field, int _alpha = mInf, int _beta = pInf, int* _next_al = new int(), int* _next_be = new int());

	~compLogic() { }
};

