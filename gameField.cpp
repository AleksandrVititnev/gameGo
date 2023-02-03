#include "gameField.h"
#include <iostream>

bool gameField::is_free(int _place_hei, int _place_wid) {
	if (_place_hei >= height_field || _place_wid >= width_field) {
		throw std::invalid_argument("GAME_FIELD::IS_FREE - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->is_free;
}

bool gameField::is_ko(int _place_hei, int _place_wid) {
	if (_place_hei >= height_field || _place_wid >= width_field) {
		throw std::invalid_argument("GAME_FIELD::IS_KO - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->is_ko;
}

char gameField::who_is(int _place_hei, int _place_wid) {
	if (_place_hei >= height_field || _place_wid >= width_field) {
		throw std::invalid_argument("GAME_FIELD::WHO_IS - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->whoIs;
}

char gameField::own_by(int _place_hei, int _place_wid) {
	if (_place_hei >= height_field || _place_wid >= width_field) {
		throw std::invalid_argument("GAME_FIELD::OWN_BY - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->ownBy;
}

int gameField::get_height() {
	return height_field;
}
int gameField::get_width() {
	return width_field;
}
int gameField::get_eatWhite() {
	return eatWhite;
}
int gameField::get_eatBlack() {
	return eatBlack;
}
int gameField::get_brethe(int _place_hei, int _place_wid) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::GET_BRETHE - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->freeBrethe;
}

bool gameField::is_self_destr(int _place_hei, int _place_wid, char _who) {
	bool result = false;
	int count1 = 0;
	int count2 = 0;

	if (_place_hei - 1 >= 0) {
		if (!field[_place_hei - 1][_place_wid]->is_free &&
			field[_place_hei - 1][_place_wid]->whoIs != _who) {
			count1++;
		}

		count2++;
	}
	if (_place_hei + 1 < height_field) {
		if (!field[_place_hei + 1][_place_wid]->is_free &&
			field[_place_hei + 1][_place_wid]->whoIs != _who) {
			count1++;
		}
		count2++;
	}
	if (_place_wid - 1 >= 0) {
		if (!field[_place_hei][_place_wid - 1]->is_free &&
			field[_place_hei][_place_wid - 1]->whoIs != _who) {
			count1++;
		}
		count2++;
	}
	if (_place_wid + 1 < height_field) {
		if (!field[_place_hei][_place_wid + 1]->is_free &&
			field[_place_hei][_place_wid + 1]->whoIs != _who) {
			count1++;
		}
		count2++;
	}

	return count1 == count2;
}

gameField& gameField::operator=(gameField& _field_from) {
	gameField new_field(_field_from.height_field, _field_from.width_field);

	field = new node**[height_field];

	for (int i{}; i < height_field; ++i) {
		field[i] = new node*[width_field];

		for (int j{}; j < width_field; ++j) {
			field[i][j] = new node();

			field[i][j]->is_free = _field_from.field[i][j]->is_free;
			field[i][j]->is_ko = _field_from.field[i][j]->is_ko;
			field[i][j]->whoIs = _field_from.field[i][j]->whoIs;
		}
	}
	
	return new_field;
}

void gameField::edit_node_free(int _place_hei, int _place_wid, bool _new_val) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_FREE - Bad int for access node.");
	}
	else {
		field[_place_hei][_place_wid]->is_free = _new_val;
	}

	return;
}

void gameField::edit_node_ko(int _place_hei, int _place_wid, bool _new_val) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_KO - Bad int for access node.");
	}
	else {
		field[_place_hei][_place_wid]->is_ko = _new_val;
	}
}

void gameField::edit_node_who(int _place_hei, int _place_wid, char _new_val) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_WHO - Bad int for access node.");
	}
	else if (_new_val != 'w' && _new_val != 'b' && _new_val != 'n') {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_WHO - Bad char for edit node.");
	}
	else {
		field[_place_hei][_place_wid]->whoIs = _new_val;
	}

	return;
}

void gameField::edit_node_brethe(int _place_hei, int _place_wid, int _new_val) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_WHO - Bad int for access node.");
	}
	else {
		field[_place_hei][_place_wid]->freeBrethe = _new_val;
	}

	return;
}

void gameField::add_eat(char who) {
	if (who == 'w') eatWhite++;
	else if (who == 'b') eatBlack++;
	else throw(std::invalid_argument("GAMEFIELD::ADD_EAT - Bad char for add eat."));
}

void gameField::set_own(int _place_hei, int _place_wid) {
	char setOwn = field[_place_hei][_place_wid]->whoIs;

	field[_place_hei][_place_wid]->ownBy = setOwn;
	if (_place_hei - 1 >= 0) {
		if (field[_place_hei - 1][_place_wid]->is_free) {
			field[_place_hei - 1][_place_wid]->ownBy = setOwn;
		}
	}
	if (_place_hei + 1 < height_field) {
		if (field[_place_hei + 1][_place_wid]->is_free) {
			field[_place_hei + 1][_place_wid]->ownBy = setOwn;
		}
	}
	if (_place_wid - 1 >= 0) {
		if (field[_place_hei][_place_wid - 1]->is_free) {
			field[_place_hei][_place_wid - 1]->ownBy = setOwn;
		}
	}
	if (_place_wid + 1 < height_field) {
		if (field[_place_hei][_place_wid + 1]->is_free) {
			field[_place_hei][_place_wid + 1]->ownBy = setOwn;
		}
	}

	return;
}

void gameField::make_turn(int _place_hei, int _place_wid, char _new_val) {
	if (!is_free(_place_hei, _place_wid)) {
		throw std::logic_error("GAME_FIELD::MAKE_TURN - This node currently busy.");
	}
	else {
		edit_node_free(_place_hei, _place_wid, false);
		edit_node_who(_place_hei, _place_wid, _new_val);
		re_calc_brethe(_place_hei, _place_wid);
		set_own(_place_hei, _place_wid);
	}

	return;
}

void gameField::restore_default(int _place_hei, int _place_wid) {
	if (is_free(_place_hei, _place_wid)) {
		throw std::logic_error("GAME_FIELD::RESTORE_DEFAULT - This node currently free.");
	}
	else {
		edit_node_free(_place_hei, _place_wid, true);
		edit_node_who(_place_hei, _place_wid, 'n');
		edit_node_brethe(_place_hei, _place_wid, 4);
	}

	return;
}

void gameField::restore_brethe(int _place_hei, int _place_wid) {
	if (_place_hei >= height_field || _place_wid >= width_field || _place_hei < 0 || _place_wid < 0) {
		return;
	}
	else if (!is_free(_place_hei, _place_wid)) {
		field[_place_hei][_place_wid]->freeBrethe++;
	}

	return;
}

void gameField::re_calc_brethe(int _place_hei, int _place_wid) {
	if (_place_hei - 1 < 0) {
		field[_place_hei][_place_wid]->freeBrethe--;
	}
	if (_place_hei + 1 >= height_field) {
		field[_place_hei][_place_wid]->freeBrethe--;
	}
	if (_place_wid - 1 < 0) {
		field[_place_hei][_place_wid]->freeBrethe--;
	}
	if (_place_wid + 1 >= height_field) {
		field[_place_hei][_place_wid]->freeBrethe--;
	}

	if (_place_hei - 1 >= 0) {
		if (!field[_place_hei - 1][_place_wid]->is_free &&
			field[_place_hei - 1][_place_wid]->whoIs != field[_place_hei][_place_wid]->whoIs) {
			field[_place_hei - 1][_place_wid]->freeBrethe--;
			field[_place_hei][_place_wid]->freeBrethe--;
		}
	}
	if (_place_hei + 1 < height_field) {
		if (!field[_place_hei + 1][_place_wid]->is_free &&
			field[_place_hei + 1][_place_wid]->whoIs != field[_place_hei][_place_wid]->whoIs) {
			field[_place_hei + 1][_place_wid]->freeBrethe--;
			field[_place_hei][_place_wid]->freeBrethe--;
		}
	}
	if (_place_wid - 1 >= 0) {
		if (!field[_place_hei][_place_wid - 1]->is_free &&
			field[_place_hei][_place_wid - 1]->whoIs != field[_place_hei][_place_wid]->whoIs) {
			field[_place_hei][_place_wid - 1]->freeBrethe--;
			field[_place_hei][_place_wid]->freeBrethe--;
		}
	}
	if (_place_wid + 1 < height_field) {
		if (!field[_place_hei][_place_wid + 1]->is_free &&
			field[_place_hei][_place_wid + 1]->whoIs != field[_place_hei][_place_wid]->whoIs) {
			field[_place_hei][_place_wid + 1]->freeBrethe--;
			field[_place_hei][_place_wid]->freeBrethe--;
		}
	}

	return;
}

void gameField::restore_default_all() {
	for (int i{}; i < height_field; ++i) {
		for (int j{}; j < width_field; ++j) {
			if (!field[i][j]->is_free) restore_default(i, j);
			field[i][j]->ownBy = 'n';
		}
	}

	return;
}

void gameField::get_own(int _place_hei, int _place_wid) {
	if (_place_hei - 1 >= 0 && !field[_place_hei - 1][_place_wid]->is_free) {
		field[_place_hei][_place_wid]->ownBy = field[_place_hei - 1][_place_wid]->ownBy;
	}
	else if (_place_hei + 1 < height_field && !field[_place_hei + 1][_place_wid]->is_free) {
		field[_place_hei][_place_wid]->ownBy = field[_place_hei + 1][_place_wid]->ownBy;
	}
	else if (_place_wid - 1 >= 0 && !field[_place_hei][_place_wid - 1]->is_free) {
		field[_place_hei][_place_wid]->ownBy = field[_place_hei][_place_wid - 1]->ownBy;
	}
	else if (_place_wid + 1 < height_field && !field[_place_hei][_place_wid + 1]->is_free) {
		field[_place_hei][_place_wid]->ownBy = field[_place_hei][_place_wid - 1]->ownBy;
	}

	return;
}

bool gameField::is_free(id_node* _node) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::IS_FREE - Nullptr _node.");
	}
	return is_free(_node->place_hei, _node->place_wid);
}

bool gameField::is_ko(id_node* _node) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::IS_KO - Nullptr _node.");
	}
	return is_ko(_node->place_hei, _node->place_wid);
}

char gameField::who_is(id_node* _node) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::WHO_IS - Nullptr _node.");
	}
	return who_is(_node->place_hei, _node->place_wid);
}

bool gameField::is_self_destr(id_node* _node, char _who) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::IS_SELF_DESTR - Nullptr _node.");
	}
	return is_self_destr(_node->place_hei, _node->place_wid, _who);
}

void gameField::edit_node_free(id_node* _node, bool _new_val) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::EDIT_NODE_FREE - Nullptr _node.");
	}
	return edit_node_free(_node->place_hei, _node->place_wid, _new_val);
}

void gameField::edit_node_ko(id_node* _node, bool _new_val) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::EDIT_NODE_KO - Nullptr _node.");
	}
	return edit_node_ko(_node->place_hei, _node->place_wid, _new_val);
}

void gameField::edit_node_who(id_node* _node, char _new_val) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::EDIT_NODE_WHO - Nullptr _node.");
	}
	return edit_node_who(_node->place_hei, _node->place_wid, _new_val);
}

void gameField::edit_node_brethe(id_node* _node, int _new_val) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::EDIT_NODE_BRETHE - Nullptr _node.");
	}
	return edit_node_brethe(_node->place_hei, _node->place_wid, _new_val);
}

void gameField::make_turn(id_node* _node, char _new_val) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::MAKE_TURN - Nullptr _node.");
	}
	return make_turn(_node->place_hei, _node->place_wid, _new_val);
}

void gameField::restore_default(id_node* _node) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::RESTORE_DEFAULT - Nullptr _node.");
	}
	return restore_default(_node->place_hei, _node->place_wid);
}

void gameField::re_calc_brethe(id_node* _node) {
	if (!_node) {
		throw std::invalid_argument("GAMEFIELD::RE_CALC_BRETHE - Nullptr _node.");
	}
	return re_calc_brethe(_node->place_hei, _node->place_wid);
}

gameField::~gameField() {
	for (int i{}; i < height_field; ++i) {
		for (int j{}; j < width_field; ++j) {
			delete field[i][j];
		}

		delete[] field[i];
	}

	delete[] field;
}