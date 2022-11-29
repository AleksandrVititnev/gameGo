//File contains computer logic.
#pragma once
#include <stdexcept>
#include "additionalFunctions.h"
#include "gameField.h"
#include "gameLogic.h"
#include "idNode.h"
#include "single_list.h"

class compLogic
{
private:
	gameLogic* rules;
	
	struct minmax_container {
		id_node* next_turn;
		int mark;
		int alpha;
		int beta;

		minmax_container(id_node* _node, int _mark, int _alpha, int _beta) : next_turn(_node), mark(_mark), alpha(_alpha), beta(_beta) { }
	};

	minmax_container* max_mm(minmax_container* _what, minmax_container* _with) {
		return _what->mark > _with->mark ? _what : _with;
	}
	minmax_container* min_mm(minmax_container* _what, minmax_container* _with) {
		return _what->mark < _with->mark ? _what : _with;
	}

	minmax_container* min_max(gameField& _field, id_node* turn, int _alpha, int _beta, char who, int depth = 0);
public:
	compLogic() : rules(nullptr) {
		rules = new gameLogic();
	}

	id_node* get_next_turn(gameField* _field);

	~compLogic() { }
};

