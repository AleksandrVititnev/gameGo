#include "gameLogic.h"

bool gameLogic::can_make_turn(gameField* _field, id_node* _node, char _who) {
	bool result = true;
	if (_node->place_hei >= _field->get_height() || _node->place_wid >= _field->get_width() ||
		_node->place_hei < 0 || _node->place_wid < 0) {
		result = false;
	}
	if (!_field->is_free(_node)) {
		result = false;
	}
	if (_field->is_ko(_node)) {
		result = false;
	}
	if (_field->is_self_destr(_node, _who)) {
		result = false;
	}

	return result;
}

void gameLogic::apply_turn(gameField* _field, id_node* _node) {
	for (int i{}; i < _field->get_height(); ++i) {
		for (int j{}; j < _field->get_width(); ++j) {
			if (_field->get_brethe(i, j) == 0) {
				//std::cout << _field->who_is(i, j) <<  ' ' << i << ' ' << j << ' ' << _field->get_brethe(i, j) << '\n';
				_field->add_eat(_field->who_is(i, j));
				_field->restore_brethe(i - 1, j);
				_field->restore_brethe(i + 1, j);
				_field->restore_brethe(i, j - 1);
				_field->restore_brethe(i, j + 1);
				_field->restore_default(i, j);
				_field->get_own(i, j);
				//std::cout << _field->who_is(i, j) << ' ' << i << ' ' << j << ' ' << _field->get_brethe(i, j) << '\n';
			}
		}
	}

	return;
}