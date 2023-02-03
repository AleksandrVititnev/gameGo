#include <iostream>
#include <SFML/Graphics.hpp>
#include "engine.h"

int main()
{
    engine eng("map4.png", "CyrilicOld.TTF");
    eng.start();

    return 0;
}