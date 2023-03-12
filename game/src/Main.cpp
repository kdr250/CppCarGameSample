#include <conio.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include "Game.h"

#define SCREEN_WIDTH  90
#define SCREEN_HEIGHT 26
#define WINDOW_WIDTH  70

Game game;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];

int carPos = WINDOW_WIDTH / 2;

void GenerateEnemy(int index)
{
    enemyX[index] = 17 + std::rand() % 33;
}

void DrawEnemy(int index)
{
    if (enemyFlag[index])
    {
        game.GoTo(Position(enemyX[index], enemyY[index]));
        std::cout << "****";
        game.GoTo(Position(enemyX[index], enemyY[index] + 1));
        std::cout << " ** ";
        game.GoTo(Position(enemyX[index], enemyY[index] + 2));
        std::cout << "****";
        game.GoTo(Position(enemyX[index], enemyY[index] + 3));
        std::cout << " ** ";
    }
}

void EraseEnemy(int index)
{
    if (enemyFlag[index])
    {
        game.GoTo(Position(enemyX[index], enemyY[index]));
        std::cout << "    ";
        game.GoTo(Position(enemyX[index], enemyY[index] + 1));
        std::cout << "    ";
        game.GoTo(Position(enemyX[index], enemyY[index] + 2));
        std::cout << "    ";
        game.GoTo(Position(enemyX[index], enemyY[index] + 3));
        std::cout << "    ";
    }
}

void ResetEnemy(int index)
{
    EraseEnemy(index);
    enemyY[index] = 1;
    GenerateEnemy(index);
}

int Collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}

void Play()
{
    carPos       = -1 + WINDOW_WIDTH / 2;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    std::system("CLS");
    game.DrawBorder();
    game.UpdateScore();
    game.GenerateEnemyCars();

    game.DisplayPlayStartMenu();

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a' || ch == 'A')
            {
                game.MoveCar(-4);
            }
            if (ch == 'd' || ch == 'D')
            {
                game.MoveCar(4);
            }
            if (ch == 27)
                break;
        }

        game.UpdateEnemyCars();

        game.DrawCar();
        game.DrawEnemyCars();

        if (Collision() == 1)
        {
            game.GameOver();
            return;
        }

        Sleep(50);
        game.EraseCar();
        game.EraseEnemyCars();
    }
}

int main()
{
    game.SetCursor(false, 0);

    srand((unsigned)time(NULL));

    while (game.IsPlaying())
    {
        game.DisplayMainMenu();

        char ch = _getche();
        switch (ch)
        {
            case '1':
                Play();
                break;
            case '2':
                game.Instructions();
                break;
            case '3':
                game.Quit();
            default:
                break;
        }
    }

    return 0;
}
