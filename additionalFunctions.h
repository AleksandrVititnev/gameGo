#pragma once
#include "gameField.h"
constexpr auto mInf = -999;
constexpr auto pInf = 999;

// Получить оценку для данной ситуации для who(w, b).
int get_mark_field(gameField* _field);
int get_mark_field2(gameField* _field, char who);