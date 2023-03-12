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

void EraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            game.GoTo(Position(j + carPos, i + 22));
            std::cout << " ";
        }
    }
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
    GenerateEnemy(0);
    GenerateEnemy(1);

    game.GoTo(Position(WINDOW_WIDTH + 7, 2));
    std::cout << "Car Game";
    game.GoTo(Position(WINDOW_WIDTH + 6, 4));
    std::cout << "----------";
    game.GoTo(Position(WINDOW_WIDTH + 6, 6));
    std::cout << "----------";
    game.GoTo(Position(WINDOW_WIDTH + 7, 12));
    std::cout << "Control ";
    game.GoTo(Position(WINDOW_WIDTH + 7, 13));
    std::cout << "----------";
    game.GoTo(Position(WINDOW_WIDTH + 2, 14));
    std::cout << " A Key - Left";
    game.GoTo(Position(WINDOW_WIDTH + 2, 15));
    std::cout << " D Key - Right";

    game.GoTo(Position(18, 5));
    std::cout << "Press any key to start!";
    _getch();
    game.GoTo(Position(18, 5));
    std::cout << "                      ";

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

        game.DrawCar();
        DrawEnemy(0);
        DrawEnemy(1);

        if (Collision() == 1)
        {
            game.GameOver();
            return;
        }

        Sleep(50);
        game.EraseCar();
        EraseEnemy(0);
        EraseEnemy(1);

        if (enemyY[0] == 10 && enemyFlag[1] == 0)
        {
            enemyFlag[1] = 1;
        }
        if (enemyFlag[0] == 1)
        {
            enemyY[0]++;
        }
        if (enemyFlag[1] == 1)
        {
            enemyY[1]++;
        }
        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            ResetEnemy(0);
            game.OneUpScore();
            game.UpdateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            ResetEnemy(1);
            game.OneUpScore();
            game.UpdateScore();
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));

    while (game.IsPlaying())
    {
        game.DisplayMenu();

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
