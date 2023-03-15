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

void PlayerCar::MoveX(int moveX)
{
    int nextPosition = this->position.x + moveX;
    if (nextPosition <= 18 || nextPosition >= 50)
        return;

    this->position.x += moveX;
}

bool PlayerCar::IsCollide(const std::unique_ptr<EnemyCar>& enemyCar)
{
    if (enemyCar->GetPosition().y + 4 >= 23)
    {
        if (enemyCar->GetPosition().x + 4 - this->position.x >= 0
            && enemyCar->GetPosition().x + 4 - this->position.x < 9)
        {
            return true;
        }
    }
    return false;
}

Position PlayerCar::GetPosition() const
{
    return this->position;
}
