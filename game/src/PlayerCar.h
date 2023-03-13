#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "EnemyCar.h"
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
    void MoveX(int moveX);
    void Erase(std::function<void(Position)> gotoFunction);
    bool IsCollide(const std::unique_ptr<EnemyCar>& enemyCar);
};
