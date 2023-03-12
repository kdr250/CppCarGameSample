#include "PlayerCar.h"

PlayerCar::PlayerCar(int windoWidth)
{
    Position position(-1 + windoWidth / 2, 22);
    this->position = position;
}

void PlayerCar::Draw(std::function<void(Position)> gotoFunction)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoFunction(this->position.Move(j, i));
            std::cout << car[i][j];
        }
    }
}

void PlayerCar::MoveX(int moveX)
{
    int nextPosition = this->position.x + moveX;
    if (nextPosition <= 18 || nextPosition >= 50)
        return;

    this->position.x += moveX;
}

void PlayerCar::Erase(std::function<void(Position)> gotoFunction)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoFunction(this->position.Move(j, i));
            std::cout << " ";
        }
    }
}
