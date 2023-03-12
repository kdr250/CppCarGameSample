#include <conio.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#define SCREEN_WIDTH  90
#define SCREEN_HEIGHT 26
#define WINDOW_WIDTH  70

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];

char car[4][4] = {
    {' ', 'Å}', 'Å}', ' '},
    {'Å}', 'Å}', 'Å}', 'Å}'},
    {' ', 'Å}', 'Å}', ' '},
    {'Å}', 'Å}', 'Å}', 'Å}'},
};

int carPos = WINDOW_WIDTH / 2;
int score  = 0;

void GoToXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void SetCursor(bool isVisible, DWORD size)
{
    if (size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = isVisible;
    lpCursor.dwSize   = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void DrawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            GoToXY(j, i);
            std::cout << "Å}";
            GoToXY(WINDOW_WIDTH - j, i);
            std::cout << "Å}";
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        GoToXY(SCREEN_WIDTH, i);
        std::cout << "Å}";
    }
}

void GenerateEnemy(int index)
{
    enemyX[index] = 17 + std::rand() % 33;
}

void DrawEnemy(int index)
{
    if (enemyFlag[index])
    {
        GoToXY(enemyX[index], enemyY[index]);
        std::cout << "****";
        GoToXY(enemyX[index], enemyY[index] + 1);
        std::cout << " ** ";
        GoToXY(enemyX[index], enemyY[index] + 2);
        std::cout << "****";
        GoToXY(enemyX[index], enemyY[index] + 3);
        std::cout << " ** ";
    }
}

void EraseEnemy(int index)
{
    if (enemyFlag[index])
    {
        GoToXY(enemyX[index], enemyY[index]);
        std::cout << "    ";
        GoToXY(enemyX[index], enemyY[index] + 1);
        std::cout << "    ";
        GoToXY(enemyX[index], enemyY[index] + 2);
        std::cout << "    ";
        GoToXY(enemyX[index], enemyY[index] + 3);
        std::cout << "    ";
    }
}

void ResetEnemy(int index)
{
    EraseEnemy(index);
    enemyY[index] = 1;
    GenerateEnemy(index);
}

void DrawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            GoToXY(j + carPos, i + 22);
            std::cout << car[i][j];
        }
    }
}

void EraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            GoToXY(j + carPos, i + 22);
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

void GameOver()
{
    std::system("CLS");
    std::cout << std::endl;
    std::cout << "\t\t--------------------------" << std::endl;
    std::cout << "\t\t-------- Game Over -------" << std::endl;
    std::cout << "\t\t--------------------------" << std::endl << std::endl;
    std::cout << "\t\tPress any key to go back to menu.";
    _getch();
}

void UpdateScore()
{
    GoToXY(WINDOW_WIDTH + 7, 5);
    std::cout << "Score: " << score << std::endl;
}

void Instructions()
{
    std::system("CLS");
    std::cout << "Instructions";
    std::cout << "\n----------------";
    std::cout << "\n Avoid Cars by moving left or right. ";
    std::cout << "\n\n Press 'a' to move left";
    std::cout << "\n Press 'd' to move right";
    std::cout << "\n Press 'escape' to exit";
    std::cout << "\n\nPress any key to go back to menu";
    _getch();
}

void Play()
{
    carPos       = -1 + WINDOW_WIDTH / 2;
    score        = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    std::system("CLS");
    DrawBorder();
    UpdateScore();
    GenerateEnemy(0);
    GenerateEnemy(1);

    GoToXY(WINDOW_WIDTH + 7, 2);
    std::cout << "Car Game";
    GoToXY(WINDOW_WIDTH + 6, 4);
    std::cout << "----------";
    GoToXY(WINDOW_WIDTH + 6, 6);
    std::cout << "----------";
    GoToXY(WINDOW_WIDTH + 7, 12);
    std::cout << "Control ";
    GoToXY(WINDOW_WIDTH + 7, 13);
    std::cout << "----------";
    GoToXY(WINDOW_WIDTH + 2, 14);
    std::cout << " A Key - Left";
    GoToXY(WINDOW_WIDTH + 2, 15);
    std::cout << " D Key - Right";

    GoToXY(18, 5);
    std::cout << "Press any key to start!";
    _getch();
    GoToXY(18, 5);
    std::cout << "                      ";

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a' || ch == 'A')
            {
                if (carPos > 18)
                {
                    carPos -= 4;
                }
            }
            if (ch == 'd' || ch == 'D')
            {
                if (carPos < 50)
                {
                    carPos += 4;
                }
            }
            if (ch == 27)
                break;
        }

        DrawCar();
        DrawEnemy(0);
        DrawEnemy(1);

        if (Collision() == 1)
        {
            GameOver();
            return;
        }

        Sleep(50);
        EraseCar();
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
            score++;
            UpdateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            ResetEnemy(1);
            score++;
            UpdateScore();
        }
    }
}

int main()
{
    SetCursor(0, 0);
    srand((unsigned)time(NULL));

    while (true)
    {
        std::system("CLS");
        GoToXY(10, 5);
        std::cout << " -------------------------- ";
        GoToXY(10, 6);
        std::cout << " |        Car Game        | ";
        GoToXY(10, 7);
        std::cout << " -------------------------- ";
        GoToXY(10, 9);
        std::cout << "1. Start Game";
        GoToXY(10, 10);
        std::cout << "2. Instructions";
        GoToXY(10, 11);
        std::cout << "3. Quit";
        GoToXY(10, 13);
        std::cout << "Select option: ";

        char ch = _getche();
        switch (ch)
        {
            case '1':
                Play();
                break;
            case '2':
                Instructions();
                break;
            case '3':
                std::exit(0);
            default:
                break;
        }
    }

    return 0;
}
