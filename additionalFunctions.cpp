#include "additionalFunctions.h"

int get_mark_field(gameField* _field) {
	int score = 0;
	int tempScore = 0;
	bool isBlack = false;
	bool isWhite = false;

	for (int i{}; i < _field->get_height(); ++i) {
		for (int j{}; j < _field->get_width(); ++j) {

			if (_field->who_is(i, j) == 'b') {
				if (isWhite) {
					isWhite = false;
					score += tempScore * 2;
				}

				isBlack = true;
			}
			else if (_field->who_is(i, j) == 'w') {
				if (isBlack) {
					isWhite = false;
					score += tempScore * 2;
				}

				isWhite = true;
			}
			else {
				tempScore++;
			}
		}
	}

	score -= _field->get_eatWhite();
	score -= _field->get_eatBlack();

	return score;
}

int get_mark_field2(gameField* _field, char who) {
	int score = 0;
	int tempScore = 0;
	bool isNeed = false;

	for (int i{}; i < _field->get_height(); ++i) {
		for (int j{}; j < _field->get_width(); ++j) {

		}
	}

	return score;
}