#pragma once

#include <functional>
#include <iostream>

#include "Position.h"

class EnemyCar
{
private:
    Position position;
    bool isAlive;

public:
    static const int NUMBER_OF_ENEMIES = 2;

    EnemyCar(Position position);

    static std::unique_ptr<EnemyCar> Generate();

    Position GetPosition();
    void Draw(std::function<void(Position)> gotoFunction);
    void MoveY(int moveY);
    void Erase(std::function<void(Position)> gotoFunction);
    void Dead();
    bool IsDead();
    bool CanSurvive(int screenHeight);
};
