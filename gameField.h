#pragma once
#include <stdexcept>
#include "idNode.h"

class gameField
{
private:
	struct node
	{
		bool is_free;		// Пустая ли клетка.
		bool is_ko;			// Правило КО.
		char whoIs;			// Кто на клетке на данный момент ('w' - белые, 'b' - чёрные, 'n' - ничейная).
		int freeBrethe;
		char ownBy;

		node() : is_free(true), is_ko(false), whoIs('n'), freeBrethe(4), ownBy('n') { }
	};

	int height_field;		// Выстота поля.
	int width_field;		// Ширина поля.
	int eatWhite;
	int eatBlack;
	node*** field;			// Указатель содержащий само поле height_field на width_field.
public:
	gameField(int _height, int _width) : height_field(_height), 
		width_field(_width), field(nullptr), eatBlack(0), eatWhite(0) {
		field = new node**[height_field];

		for (int i{}; i < height_field; ++i) {
			field[i] = new node * [width_field];

			for (int j{}; j < width_field; ++j) {
				field[i][j] = new node();
			}
		}
	}

	gameField(gameField* _field) : eatBlack(0), eatWhite(0){
		height_field = _field->height_field;
		width_field = _field->width_field;
		field = new node * *[height_field];

		for (int i{}; i < height_field; ++i) {
			field[i] = new node * [width_field];

			for (int j{}; j < width_field; ++j) {
				field[i][j] = new node();

				field[i][j]->is_free = _field->field[i][j]->is_free;
				field[i][j]->is_ko = _field->field[i][j]->is_ko;
				field[i][j]->whoIs = _field->field[i][j]->whoIs;
				field[i][j]->ownBy = _field->field[i][j]->ownBy;
			}
		}
	}

	void copy_field(gameField* _field) {
		height_field = _field->height_field;
		width_field = _field->width_field;
		eatBlack = _field->eatBlack;
		eatWhite = _field->eatWhite;
		field = new node * *[height_field];

		for (int i{}; i < height_field; ++i) {
			field[i] = new node * [width_field];

			for (int j{}; j < width_field; ++j) {
				field[i][j] = new node();

				field[i][j]->is_free = _field->field[i][j]->is_free;
				field[i][j]->is_ko = _field->field[i][j]->is_ko;
				field[i][j]->whoIs = _field->field[i][j]->whoIs;
				field[i][j]->ownBy = _field->field[i][j]->ownBy;
			}
		}
	}

	bool is_free(int _place_hei, int _place_wid);
	bool is_ko(int _place_hei, int _place_wid);
	char who_is(int _place_hei, int _place_wid);
	char own_by(int _place_hei, int _place_wid);
	bool is_self_destr(int _place_hei, int _place_wid, char _who);
	

	int get_height();
	int get_width();
	int get_eatWhite();
	int get_eatBlack();
	int get_brethe(int _place_hei, int _place_wid);

	gameField& operator=(gameField& _field_from);

	void edit_node_free(int _place_hei, int _place_wid, bool _new_val);
	void edit_node_ko(int _place_hei, int _place_wid, bool _new_val);
	void edit_node_who(int _place_hei, int _place_wid, char _new_val);
	void edit_node_brethe(int _place_hei, int _place_wid, int _new_val);
	

	void add_eat(char who);
	void set_own(int _place_hei, int _place_wid);
	void make_turn(int _place_hei, int _place_wid, char _new_val);
	void restore_default(int _place_hei, int _place_wid);
	void restore_brethe(int _place_hei, int _place_wid);
	void re_calc_brethe(int _place_hei, int _place_wid);
	void restore_default_all();
	
	void get_own(int _place_hei, int _place_wid);

	bool is_free(id_node* _node);
	bool is_ko(id_node* _node);
	char who_is(id_node* _node);
	bool is_self_destr(id_node* _node, char _who);
	void edit_node_free(id_node* _node, bool _new_val);
	void edit_node_ko(id_node* _node, bool _new_val);
	void edit_node_who(id_node* _node, char _new_val);
	void edit_node_brethe(id_node* _node, int _new_val);
	void make_turn(id_node* _node, char _new_val);
	void restore_default(id_node* _node);
	void re_calc_brethe(id_node* _node);

	~gameField();
};

