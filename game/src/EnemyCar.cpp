#include "EnemyCar.h"

EnemyCar::EnemyCar(Position position)
{
    this->position = position;
    this->isAlive  = true;
}

std::unique_ptr<EnemyCar> EnemyCar::Generate()
{
    int randomX = 17 + std::rand() % 33;
    Position position(randomX, 1);
    return std::make_unique<EnemyCar>(position);
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
    this->position.y += moveY;
}

void EnemyCar::Erase(std::function<void(Position)> gotoFunction)
{
    gotoFunction(this->position);
    std::cout << "    ";
    gotoFunction(this->position.MoveY(1));
    std::cout << "    ";
    gotoFunction(this->position.MoveY(2));
    std::cout << "    ";
    gotoFunction(this->position.MoveY(3));
    std::cout << "    ";
}

void EnemyCar::Dead()
{
    this->isAlive = false;
}

bool EnemyCar::IsDead()
{
    return !isAlive;
}

bool EnemyCar::CanSurvive(int screenHeight)
{
    return this->position.y <= screenHeight - 4;
}
