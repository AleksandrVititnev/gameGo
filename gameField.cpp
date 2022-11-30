#include "gameField.h"

bool gameField::is_free(int _place_hei, int _place_wid) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::IS_FREE - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->is_free;
}

bool gameField::is_ko(int _place_hei, int _place_wid) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::IS_KO - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->is_ko;
}

char gameField::who_is(int _place_hei, int _place_wid) {
	if (_place_hei > height_field || _place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::WHO_IS - Bad int for access node.");
	}

	return field[_place_hei][_place_wid]->whoIs;
}

bool gameField::is_free(id_node* _node) {
	if (_node->place_hei > height_field || _node->place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::IS_FREE - Bad int for access node.");
	}

	return field[_node->place_hei][_node->place_wid]->is_free;
}

bool gameField::is_ko(id_node* _node) {
	if (_node->place_hei > height_field || _node->place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::IS_KO - Bad int for access node.");
	}

	return field[_node->place_hei][_node->place_wid]->is_ko;
}

char gameField::who_is(id_node* _node) {
	if (_node->place_hei > height_field || _node->place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::WHO_IS - Bad int for access node.");
	}

	return field[_node->place_hei][_node->place_wid]->whoIs;
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

bool gameField::is_self_destr(int _place_hei, int _place_wid, char _who) {
	bool result = false;

	if (_place_hei + 2 > height_field || _place_wid + 2 > width_field || _place_hei < 0 || _place_wid < 0) {
		throw std::invalid_argument("GAME_FIELD::WHO_IS - Bad int for access node.");
	}
	if (_place_hei + 1 == height_field || _place_wid + 1 == width_field) {
		if (field[_place_hei - 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid - 1]->whoIs != _who) {
			result = true;
		}
		else if (field[_place_hei - 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid + 1]->whoIs != _who) {
			result = true;
		}
		else if (field[_place_hei - 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid - 1]->whoIs != _who &&
			field[_place_hei + 1][_place_wid]->whoIs != _who) {
			result = true;
		}
		else if (field[_place_hei - 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid + 1]->whoIs != _who &&
			field[_place_hei][_place_wid - 1]->whoIs != _who) {
			result = true;
		}
	}
	else if (_place_hei - 1 == height_field || _place_wid - 1 == width_field) {
		if (field[_place_hei + 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid + 1]->whoIs != _who) {
			result = true;
		}
		else if (field[_place_hei + 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid - 1]->whoIs != _who) {
			result = true;
		}
		else if (field[_place_hei - 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid + 1]->whoIs != _who &&
			field[_place_hei + 1][_place_wid]->whoIs != _who) {
			result = true;
		}
		else if (field[_place_hei + 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid + 1]->whoIs != _who &&
			field[_place_hei][_place_wid - 1]->whoIs != _who) {
			result = true;
		}
	}
	else if (field[_place_hei + 1][_place_wid]->whoIs != _who && field[_place_hei][_place_wid + 1]->whoIs != _who &&
		field[_place_hei][_place_wid - 1]->whoIs != _who && field[_place_hei - 1][_place_wid]->whoIs != _who) {
		result = true;;
	}

	return result;
}

bool gameField::is_self_destr(id_node* _node, char _who) {

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

void gameField::edit_node_free(id_node* _node, bool _new_val) {
	if (_node->place_hei > height_field || _node->place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_FREE - Bad int for access node.");
	}
	else {
		field[_node->place_hei][_node->place_wid]->is_free = _new_val;
	}

	return;
}
void gameField::edit_node_ko(id_node* _node, bool _new_val) {
	if (_node->place_hei > height_field || _node->place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_KO - Bad int for access node.");
	}
	else {
		field[_node->place_hei][_node->place_wid]->is_ko = _new_val;
	}
}
void gameField::edit_node_who(id_node* _node, char _new_val) {
	if (_node->place_hei > height_field || _node->place_wid > width_field) {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_WHO - Bad int for access node.");
	}
	else if (_new_val != 'w' && _new_val != 'b' && _new_val != 'n') {
		throw std::invalid_argument("GAME_FIELD::EDIT_NODE_WHO - Bad char for edit node.");
	}
	else {
		field[_node->place_hei][_node->place_wid]->whoIs = _new_val;
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
	}

	return;
}
void gameField::make_turn(id_node* _node, char _new_val) {
	if (!is_free(_node)) {
		throw std::logic_error("GAME_FIELD::MAKE_TURN - This node currently busy.");
	}
	else {
		edit_node_free(_node, false);
		edit_node_who(_node, _new_val);
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
	}

	return;
}
void gameField::restore_default(id_node* _node) {
	if (is_free(_node)) {
		throw std::logic_error("GAME_FIELD::RESTORE_DEFAULT - This node currently busy.");
	}
	else {
		edit_node_free(_node, true);
		edit_node_who(_node, 'n');
	}

	return;
}