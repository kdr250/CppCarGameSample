#include <conio.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include "Game.h"

Game game;

void Play()
{
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

        if (game.IsCollide())
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
