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

		minmax_container(id_node* _node, int _mark) : next_turn(_node), mark(_mark) { }
		~minmax_container() {
			delete next_turn;
		}
	};

	minmax_container* max_mm(minmax_container* _what, minmax_container* _with) {
		if (!_what) return _with;
		if (!_with) return _what;

		return _what->mark > _with->mark ? _what : _with;
	}
	minmax_container* min_mm(minmax_container* _what, minmax_container* _with) {
		if (!_what) return _with;
		if (!_with) return _what;

		return _what->mark < _with->mark ? _what : _with;
	}

	minmax_container* min_max(gameField& _field, id_node* turn, int _alpha, int _beta, char who, int depth = 0);
	minmax_container* min_max2(gameField* field, int _alpha, int _beta, char who, int depth = 0);
public:
	compLogic(gameLogic* _rules) : rules(_rules) {	}

	id_node* get_next_turn(gameField* _field);

	~compLogic() { }
};

