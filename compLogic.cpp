#include "compLogic.h"

// Рекурсивная функция минимакса
compLogic::minmax_container* compLogic::min_max(gameField& _field, id_node* turn, int _alpha, int _beta, char who, int depth = 0) {

	minmax_container* mmc = nullptr;													// Контейнер для переноса значений хода и alpha, beta фун-кций.
	id_node* now_turn = nullptr;														// Контейнер для координат текущего хода.
	single_list<minmax_container*>* lst_cont = new single_list<minmax_container*>();	// Связный список для хранения контейнеров сыновей узла.
	gameField copy_field = _field;														// Копия игрового поля.
	int now_mark;																		// Переменная для хранения оценки.

	if (depth == 4) {															// Встречаем 5-ый ход и обрабатываем последний.
		copy_field.make_turn(turn, who);										// Поставить фгуру на стол.
		rules->apply_turn(&copy_field, turn);									// Применить ход (распознать ситуации захвата противника).

		now_mark = get_mark_field(&copy_field);									// Получить оценку поля.

		if (who == 'w') {														// Ход был за нами.
			mmc = new minmax_container(turn, now_mark, _alpha, now_mark);
		}
		else {																	// Ход был за противником.
			mmc = new minmax_container(turn, now_mark, now_mark, _beta);
		}
	}
	else {
		if (turn) {																					// Если не корень абстрактного дерева, то сделать ход.
			copy_field.make_turn(turn, who);
			rules->apply_turn(&copy_field, turn);
		}
		for (int i{}; i < copy_field.get_height(); ++i) {
			for (int j{}; j < copy_field.get_width(); ++j) {
				now_turn = new id_node(i, j);

				if (copy_field.is_free(now_turn) && rules->can_make_turn(&copy_field, now_turn, who)) {		// Если можем сходить.

					if (who == 'w') {																// Ход был за нами.
						depth++;
						mmc = min_max(copy_field, now_turn, _alpha, _beta, 'b', depth);
					}
					else {																			// Ход был за противником.
						depth++;
						mmc = min_max(copy_field, now_turn, _alpha, _beta, 'w', depth);
					}

					lst_cont->push_back(mmc);														// Добавить в список контейнер с информацией о ходе

					if (who == 'w' && mmc && mmc->alpha > _alpha) {									// Ход был за нами и альфа хода больше, чем текущая.
						_alpha = mmc->alpha;
					}
					else if (who == 'b' && mmc && mmc->beta < _beta) {								// Ход был за нами и бета хода меньше, чем текущая.
						_alpha = mmc->alpha;
					}

					if (_alpha > _beta) break;														// Отсекаем ходы, которые нам не походят.
				}
			}
			if (_alpha > _beta) break;																// Отсекаем ходы, которые нам не походят.
		}

		for (int i{}; i < lst_cont->get_count_elem(); ++i) {
			if (who == 'w') {																		// Ход был за нами.
				mmc = max_mm(mmc, lst_cont->get_value(i));											// Ищем максимальное занчение ОФ.
			}
			else {																					// Ход был за противником.
				mmc = min_mm(mmc, lst_cont->get_value(i));											// Ищем минимальное занчение ОФ.
			}
		}
		if (who == 'w') {																			// Ход был за нами.
			mmc->beta = mmc->alpha;																	// Применяем границы.
			mmc->alpha = mInf;
		}
		else {																						// Ход был за противником.
			mmc->alpha = mmc->beta;																	// Применяем границы.
			mmc->beta = pInf;
		}
	}

	return mmc;
}

// Обёртка для вызова функции минимакса.
id_node* compLogic::get_next_turn(gameField* _field) {

	minmax_container* mmc = nullptr;
	gameField copy_field = *_field;

	mmc = min_max(copy_field, nullptr, mInf, pInf, 'w');

	return mmc->next_turn;
}