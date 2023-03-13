#include <conio.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include "Game.h"

int main()
{
    Game game;

    game.SetCursor(false, 0);

    srand((unsigned)time(NULL));

    while (game.IsContinuing())
    {
        game.DisplayMainMenu();

        char ch = _getche();
        switch (ch)
        {
            case '1':
                game.Play();
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
