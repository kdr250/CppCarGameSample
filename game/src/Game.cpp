#include <conio.h>
#include <iostream>

#include "Game.h"

Game::Game()
{
    this->isContinuing = true;
    this->isPlaying    = false;
    this->console      = GetStdHandle(STD_OUTPUT_HANDLE);
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

bool Game::IsContinuing() const
{
    return this->isContinuing;
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
    CONSOLE_CURSOR_INFO lpCursor {};
    lpCursor.bVisible = isVisible;
    lpCursor.dwSize   = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void Game::GameOver()
{
    this->enemyCars.clear();
    this->isPlaying = false;
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
    this->playerCar->MoveX(moveX);
}

void Game::EraseCar()
{
    this->playerCar->Erase(gotoFunction);
}

void Game::Quit()
{
    isContinuing = false;
}

void Game::DisplayMainMenu()
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

void Game::DisplayPlayStartMenu()
{
    GoTo(Position(WINDOW_WIDTH + 7, 2));
    std::cout << "Car Game";
    GoTo(Position(WINDOW_WIDTH + 6, 4));
    std::cout << "----------";
    GoTo(Position(WINDOW_WIDTH + 6, 6));
    std::cout << "----------";
    GoTo(Position(WINDOW_WIDTH + 7, 12));
    std::cout << "Control ";
    GoTo(Position(WINDOW_WIDTH + 7, 13));
    std::cout << "----------";
    GoTo(Position(WINDOW_WIDTH + 2, 14));
    std::cout << " A Key - Left";
    GoTo(Position(WINDOW_WIDTH + 2, 15));
    std::cout << " D Key - Right";

    GoTo(Position(18, 5));
    std::cout << "Press any key to start!";
    _getch();
    GoTo(Position(18, 5));
    std::cout << "                      ";
}

void Game::GenerateEnemyCars()
{
    enemyCars.push_back(EnemyCar::Generate());
    enemyCars.push_back(EnemyCar::Generate());
}

void Game::UpdateEnemyCars()
{
    std::for_each(enemyCars.begin(),
                  enemyCars.end(),
                  [this](std::unique_ptr<EnemyCar>& enemy)
                  {
                      enemy->MoveY(1);
                      if (!enemy->CanSurvive(SCREEN_HEIGHT))
                      {
                          this->OneUpScore();
                          this->UpdateScore();
                          enemy->Dead();
                      }
                  });

    enemyCars.erase(std::remove_if(std::begin(enemyCars),
                                   std::end(enemyCars),
                                   [](std::unique_ptr<EnemyCar>& enemy)
                                   {
                                       return enemy->IsDead();
                                   }),
                    std::cend(enemyCars));

    int diff = EnemyCar::NUMBER_OF_ENEMIES - enemyCars.size();
    for (int i = 0; i < diff; i++)
    {
        enemyCars.push_back(EnemyCar::Generate());
    }
}

void Game::DrawEnemyCars()
{
    std::for_each(enemyCars.begin(),
                  enemyCars.end(),
                  [this](std::unique_ptr<EnemyCar>& enemy)
                  {
                      enemy->Draw(gotoFunction);
                  });
}

bool Game::IsCollide()
{
    return std::any_of(this->enemyCars.begin(),
                       this->enemyCars.end(),
                       [this](std::unique_ptr<EnemyCar>& enemyCar)
                       {
                           return this->playerCar->IsCollide(enemyCar);
                       });
}

void Game::EraseEnemyCars()
{
    std::for_each(enemyCars.begin(),
                  enemyCars.end(),
                  [this](std::unique_ptr<EnemyCar>& enemy)
                  {
                      enemy->Erase(this->gotoFunction);
                  });
}

void Game::Play()
{
    std::system("CLS");
    this->DrawBorder();
    this->UpdateScore();
    this->GenerateEnemyCars();

    this->DisplayPlayStartMenu();
    this->isPlaying = true;

    while (isPlaying)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a' || ch == 'A')
            {
                this->MoveCar(-4);
            }
            if (ch == 'd' || ch == 'D')
            {
                this->MoveCar(4);
            }
            if (ch == 27)
                break;
        }

        this->UpdateEnemyCars();

        this->DrawCar();
        this->DrawEnemyCars();

        if (this->IsCollide())
        {
            this->GameOver();
            return;
        }

        Sleep(50);
        this->EraseCar();
        this->EraseEnemyCars();
    }
}
