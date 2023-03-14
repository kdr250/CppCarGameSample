#pragma once

#include <windows.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "PlayerCar.h"

class Game
{
private:
    HANDLE console;
    COORD cursorPosition;
    bool isContinuing;
    bool isPlaying;
    int score;
    std::unique_ptr<PlayerCar> playerCar;
    std::vector<std::unique_ptr<EnemyCar>> enemyCars;
    std::function<void(Position)> gotoFunction;

    void GoTo(Position position);
    void GameOver();
    void UpdateScore();
    void DrawBorder();
    void OneUpScore();
    void DrawCar();
    void MoveCar(int moveX);
    void EraseCar();
    void GenerateEnemyCar();
    void UpdateEnemyCars();
    void DrawEnemyCars();
    void EraseEnemyCars();
    bool IsCollide();

public:
    static const int SCREEN_WIDTH  = 90;
    static const int SCREEN_HEIGHT = 26;
    static const int WINDOW_WIDTH  = 70;

    Game();

    bool IsContinuing() const;
    void SetCursor(bool isVisible, DWORD size);
    void Instructions();
    void DisplayMainMenu();
    void DisplayPlayStartMenu();
    void Play();
    void Quit();
};
