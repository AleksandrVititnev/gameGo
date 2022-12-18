#include "compLogic.h"
int counter = 0;
// Рекурсивная функция минимакса
//compLogic::minmax_container* compLogic::min_max(gameField& _field, id_node* turn, int _alpha, int _beta, char who, int depth) {
//
//	minmax_container* mmc = nullptr;													// Контейнер для переноса значений хода и alpha, beta фун-кций.
//	id_node* now_turn = nullptr;														// Контейнер для координат текущего хода.
//	single_list<minmax_container*>* lst_cont = new single_list<minmax_container*>();	// Связный список для хранения контейнеров сыновей узла.
//	//gameField copy_field = _field;														 Копия игрового поля.
//	gameField copy_field(_field);
//	int now_mark;																		// Переменная для хранения оценки.
//
//	if (depth == 4) {															// Встречаем 5-ый ход и обрабатываем последний.
//		copy_field.make_turn(turn, who);										// Поставить фгуру на стол.
//		rules->apply_turn(&copy_field, turn);									// Применить ход (распознать ситуации захвата противника).
//
//		//now_mark = get_mark_field(&copy_field);									// Получить оценку поля.
//		now_mark = turn->place_hei * turn->place_wid;
//
//		if (who == 'w') {														// Ход был за нами.
//			mmc = new minmax_container(turn, now_mark, _alpha, now_mark);
//		}
//		else {																	// Ход был за противником.
//			mmc = new minmax_container(turn, now_mark, now_mark, _beta);
//		}
//	}
//	else {
//		if (turn) {																					// Если не корень абстрактного дерева, то сделать ход.
//			copy_field.make_turn(turn, who);
//			rules->apply_turn(&copy_field, turn);
//		}
//		for (int i{}; i < copy_field.get_height(); ++i) {
//			for (int j{}; j < copy_field.get_width(); ++j) {
//				now_turn = new id_node(i, j);
//
//				if (copy_field.is_free(now_turn) && rules->can_make_turn(&copy_field, now_turn, who)) {		// Если можем сходить.
//
//					if (who == 'w') {																// Ход был за нами.
//						depth++;
//						mmc = min_max(copy_field, now_turn, _alpha, _beta, 'b', depth);
//					}
//					else {																			// Ход был за противником.
//						depth++;
//						mmc = min_max(copy_field, now_turn, _alpha, _beta, 'w', depth);
//					}
//
//					lst_cont->push_back(mmc);														// Добавить в список контейнер с информацией о ходе
//
//					if (who == 'w' && mmc && mmc->alpha > _alpha) {									// Ход был за нами и альфа хода больше, чем текущая.
//						_alpha = mmc->alpha;
//					}
//					else if (who == 'b' && mmc && mmc->beta < _beta) {								// Ход был за нами и бета хода меньше, чем текущая.
//						_alpha = mmc->alpha;
//					}
//
//					if (_alpha > _beta) break;														// Отсекаем ходы, которые нам не походят.
//				}
//			}
//			if (_alpha > _beta) break;																// Отсекаем ходы, которые нам не походят.
//		}
//
//		for (int i{}; i < lst_cont->get_count_elem(); ++i) {
//			if (who == 'w') {																		// Ход был за нами.
//				mmc = max_mm(mmc, lst_cont->get_value(i));											// Ищем максимальное занчение ОФ.
//			}
//			else {																					// Ход был за противником.
//				mmc = max_mm(mmc, lst_cont->get_value(i));											// Ищем минимальное занчение ОФ.
//			}
//		}
//		if (mmc) {
//			if (who == 'w') {																			// Ход был за нами.
//				mmc->beta = mmc->alpha;																	// Применяем границы.
//				mmc->alpha = mInf;
//			}
//			else {																						// Ход был за противником.
//				mmc->alpha = mmc->beta;																	// Применяем границы.
//				mmc->beta = pInf;
//			}
//
//			mmc->next_turn = now_turn;
//		}
//	}
//
//	return mmc;
//}

compLogic::minmax_container* compLogic::min_max2(gameField* field, int _alpha, int _beta, char who, int depth) {
	minmax_container* mmc = nullptr;
	minmax_container* mmc_sel = nullptr;
	id_node* now_turn = nullptr;
	//single_list<minmax_container*>* lst_cont = new single_list<minmax_container*>();
	gameField* copy = nullptr;
	int now_mark;
	counter++;

	/*if (counter == 223) {
		for (int i{}; i < 9; ++i) {
			for (int j{}; j < 9; ++j) {
				std::cout << i << "^" << j << ":" << field->who_is(i, j) << '*';
			}
			std::cout << "\n";
		}
	}*/

	if (depth == 4) {
		//now_mark = get_mark_field(copy);
		now_mark = counter;

		mmc = new minmax_container(nullptr, now_mark);

		return mmc;
	}
	else {
		now_turn = new id_node(0, 0);
		copy = new gameField(field);
		for (int i{}; i < copy->get_height() && _alpha < _beta; ++i) {
			for (int j{}; j < copy->get_width() && _alpha < _beta; ++j) {
				now_turn->place_hei = i;
				now_turn->place_wid = j;

				if (rules->can_make_turn(copy, now_turn, who)) {
					if (who == 'w') {
						copy->make_turn(now_turn, who);
						rules->apply_turn(copy, now_turn);

						depth++;

						mmc = min_max2(copy, _alpha, _beta, 'b', depth);

						mmc->next_turn = now_turn; // mmc иногда nullptr
						
						depth--;
					}
					else {
						copy->make_turn(now_turn, who);
						rules->apply_turn(copy, now_turn);

						depth++;

						mmc = min_max2(copy, _alpha, _beta, 'w', depth);

						mmc->next_turn = now_turn; // mmc иногда nullptr

						depth--;
					}

					if (who == 'w') {
						mmc_sel = max_mm(mmc_sel, mmc);
						_alpha = mmc_sel->mark;
					}
					if (who == 'b') {
						mmc_sel = min_mm(mmc_sel, mmc);
						_beta = mmc_sel->mark;
					}

					if (copy) {
						delete copy;
						copy = new gameField(field);
					}
				}
			}
		}
	}

	if (copy) {
		delete copy;
	}
	return mmc_sel;
}

// Обёртка для вызова функции минимакса.
id_node* compLogic::get_next_turn(gameField* _field) {

	minmax_container* mmc = nullptr;
	//gameField copy_field(_field);
	mmc = min_max2(_field, mInf, pInf, 'w');

	return mmc->next_turn;
}