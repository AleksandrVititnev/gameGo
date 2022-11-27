#pragma once

// Структура для передачи координат клетки.
struct id_node {
	int place_hei;
	int place_wid;

	id_node(int _hei, int _wid) : place_hei(_hei), place_wid(_wid) { }
};