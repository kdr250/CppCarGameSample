#include <conio.h>
#include <iostream>

#include "Game.h"

Game::Game()
{
    this->isPlaying = true;
    this->console   = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition {};
    cursorPosition.X     = 0;
    cursorPosition.Y     = 0;
    this->cursorPosition = cursorPosition;
    this->score          = 0;
    this->playerCar      = std::make_unique<PlayerCar>(WINDOW_WIDTH);
    this->gotoFunction   = [this](Position position)
    {
        this->GoTo(position);
    };
}

bool Game::IsPlaying() const
{
    return this->isPlaying;
}

void Game::GoTo(Position position)
{
    this->cursorPosition.X = position.x;
    this->cursorPosition.Y = position.y;
    SetConsoleCursorPosition(console, cursorPosition);
}

void Game::SetCursor(bool isVisible, DWORD size)
{
    if (size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = isVisible;
    lpCursor.dwSize   = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void Game::GameOver()
{
    std::system("CLS");
    std::cout << std::endl;
    std::cout << "\t\t--------------------------" << std::endl;
    std::cout << "\t\t-------- Game Over -------" << std::endl;
    std::cout << "\t\t--------------------------" << std::endl << std::endl;
    std::cout << "\t\tPress any key to go back to menu.";
    _getch();
}

void Game::UpdateScore()
{
    GoTo(Position(WINDOW_WIDTH + 7, 5));
    std::cout << "Score: " << score << std::endl;
}

void Game::Instructions()
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

void Game::DrawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            GoTo(Position(j, i));
            std::cout << "}";
            GoTo(Position(WINDOW_WIDTH - j, i));
            std::cout << "}";
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        GoTo(Position(SCREEN_WIDTH, i));
        std::cout << "}";
    }
}

void Game::OneUpScore()
{
    this->score++;
}

void Game::DrawCar()
{
    this->playerCar->Draw(gotoFunction);
}

void Game::MoveCar(int moveX)
{
    this->playerCar->Move(moveX);
}

void Game::EraseCar()
{
    this->playerCar->Erase(gotoFunction);
}

void Game::Quit()
{
    isPlaying = false;
}

void Game::DisplayMenu()
{
    std::system("CLS");
    GoTo(Position(10, 5));
    std::cout << " -------------------------- ";
    GoTo(Position(10, 6));
    std::cout << " |        Car Game        | ";
    GoTo(Position(10, 7));
    std::cout << " -------------------------- ";
    GoTo(Position(10, 9));
    std::cout << "1. Start Game";
    GoTo(Position(10, 10));
    std::cout << "2. Instructions";
    GoTo(Position(10, 11));
    std::cout << "3. Quit";
    GoTo(Position(10, 13));
    std::cout << "Select option: ";
}
