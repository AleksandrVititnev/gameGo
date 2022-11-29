#include "compLogic.h"

compLogic::minmax_container* compLogic::min_max(gameField& _field, id_node* turn, int _alpha, int _beta, char who, int depth = 0) {
	minmax_container* mmc = nullptr;
	id_node* now_turn = nullptr;
	single_list<minmax_container*>* lst_cont = new single_list<minmax_container*>();
	gameField copy_field = _field;
	int now_mark;

	if (depth == 4) {
		_field.make_turn(turn, who);
		rules->apply_turn(&_field, turn);

		now_mark = get_mark_field(&_field, who);

		if (who == 'w') {
			mmc = new minmax_container(turn, now_mark, _alpha, now_mark);
		}
		else {
			mmc = new minmax_container(turn, now_mark, now_mark, _beta);
		}

		return mmc;
	}
	else {
		if (turn) {
			_field.make_turn(turn, who);
			rules->apply_turn(&_field, turn);
		}
		for (int i{}; i < _field.get_height(); ++i) {
			for (int j{}; j < _field.get_width(); ++j) {
				now_turn = new id_node(i, j);

				if (_field.is_free(now_turn) && rules->can_make_turn(&_field, now_turn, who)) {

					if (who == 'w') {
						mmc = min_max(_field, now_turn, _alpha, _beta, 'b');
					}
					else {
						mmc = min_max(_field, now_turn, _alpha, _beta, 'w');
					}

					lst_cont->push_back(mmc);

					if (who == 'w' && mmc && mmc->alpha > _alpha) {
						_alpha = mmc->alpha;
					}
					else if (who == 'b' && mmc && mmc->beta < _beta) {
						_alpha = mmc->alpha;
					}

					if (_alpha > _beta) break;
				}
			}
			if (_alpha > _beta) break;
		}

		for (int i{}; i < lst_cont->get_count_elem(); ++i) {
			if (who == 'w') {
				mmc = max_mm(mmc, lst_cont->get_value(i));
			}
			else {
				mmc = min_mm(mmc, lst_cont->get_value(i));
			}
		}
		if (who == 'w') {
			mmc->beta = mmc->alpha;
			mmc->alpha = mInf;
		}
		else {
			mmc->alpha = mmc->beta;
			mmc->beta = pInf;
		}
	}

	return mmc;
}

id_node* compLogic::get_next_turn(gameField* _field) {

	minmax_container* mmc = nullptr;
	gameField copy_field = *_field;

	mmc = min_max(copy_field, nullptr, mInf, pInf, 'w');

	return mmc->next_turn;
}