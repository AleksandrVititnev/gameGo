#include "compLogic.h"

id_node* compLogic::get_next_turn(gameField* _field, int _alpha = mInf, int _beta = pInf, int* _next_al = new int(), int* _next_be = new int()) {
	id_node* now_turn = nullptr;
	id_node* next_turn = nullptr;
	int mark = 0;

	for (int turn{}; turn < 5; ++turn) {
		for (int i{}; i < _field->get_height(); ++i) {
			for (int j{}; j < _field->get_width(); ++j) {
				now_turn = new id_node(i, j);

				if (_field->is_free(now_turn) && rules->can_make_turn(_field, now_turn, 'w')) {
					_field->make_turn(now_turn, 'w');
					rules->apply_turn(_field, now_turn);

					next_turn = get_next_turn(_field, _alpha, _beta, _next_al, _next_be);
				}
			}
		}
	}


}