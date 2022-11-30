#pragma once
#include "gameField.h"
#define mInf -999999
#define pInf 999999

// Получить оценку для данной ситуации для who(w, b).
int get_mark_field(gameField* _field, char _who);