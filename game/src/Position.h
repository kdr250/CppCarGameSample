#pragma once

struct Position
{
public:
    int x;
    int y;

    Position()
    {
        this->x = 0;
        this->y = 0;
    }

    Position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position Move(int moveX, int moveY)
    {
        int newX = this->x + moveX;
        int newY = this->y + moveY;
        return Position(newX, newY);
    }

    Position MoveX(int moveX)
    {
        int newX = this->x + moveX;
        int newY = this->y;
        return Position(newX, newY);
    }

    Position MoveY(int moveY)
    {
        int newX = this->x;
        int newY = this->y + moveY;
        return Position(newX, newY);
    }
};
