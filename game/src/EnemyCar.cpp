#include "EnemyCar.h"

EnemyCar::EnemyCar(Position position)
{
    this->position = position;
}

EnemyCar EnemyCar::Generate()
{
    int randomX = 17 + std::rand() % 33;
    Position position(randomX, 1);
    return EnemyCar(position);
}

Position EnemyCar::GetPosition()
{
    return this->position;
}

void EnemyCar::Draw(std::function<void(Position)> gotoFunction)
{
    gotoFunction(this->position);
    std::cout << "****";
    gotoFunction(this->position.MoveY(1));
    std::cout << " ** ";
    gotoFunction(this->position.MoveY(2));
    std::cout << "****";
    gotoFunction(this->position.MoveY(3));
    std::cout << " ** ";
}

void EnemyCar::MoveY(int moveY)
{
    this->position.MoveY(moveY);
}
