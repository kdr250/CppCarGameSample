#pragma once

#include <functional>
#include <iostream>

#include "Position.h"

class EnemyCar
{
private:
    Position position;

public:
    EnemyCar(Position position);

    static EnemyCar Generate();

    Position GetPosition();
    void Draw(std::function<void(Position)> gotoFunction);
    void MoveY(int moveY);
};
