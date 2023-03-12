#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Position.h"

class PlayerCar
{
private:
    Position position;
    char car[4][4] = {
        {' ', '+', '+', ' '},
        {'+', '+', '+', '+'},
        {' ', '+', '+', ' '},
        {'+', '+', '+', '+'},
    };

public:
    PlayerCar(int windowWidth);

    void Draw(std::function<void(Position)> gotoFunction);
    void Move(int moveX);
    void Erase(std::function<void(Position)> gotoFunction);
};
