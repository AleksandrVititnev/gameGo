#include "gameLogic.h"

bool gameLogic::can_make_turn(gameField* _field, id_node* _node, char _who) {
	bool result = true;
	if (!_field->is_free(_node)) {
		result = false;
	}
	if (_field->is_ko(_node)) {
		result = false;
	}
	/*if (_field->is_self_destr(_node, _who)) {
		result = false;
	}*/

	return result;
}

void gameLogic::apply_turn(gameField* _field, id_node* _node) {
	for (int i{}; i < _field->get_height(); ++i) {
		for (int j{}; j < _field->get_width(); ++j) {
			if (_field->get_brethe(i, j) == 0) {
				_field->restore_default(i, j);
			}
		}
	}

	return;
}