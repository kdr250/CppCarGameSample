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
    bool isPlaying;
    HANDLE console;
    COORD cursorPosition;

    std::unique_ptr<PlayerCar> playerCar;
    std::vector<std::unique_ptr<EnemyCar>> enemyCars;

    int score;

    std::function<void(Position)> gotoFunction;

public:
    static const int SCREEN_WIDTH  = 90;
    static const int SCREEN_HEIGHT = 26;
    static const int WINDOW_WIDTH  = 70;

    Game();

    bool IsPlaying() const;
    void GoTo(Position position);
    void SetCursor(bool isVisible, DWORD size);
    void GameOver();
    void UpdateScore();
    void Instructions();
    void DrawBorder();
    void OneUpScore();
    void DrawCar();
    void MoveCar(int moveX);
    void EraseCar();
    void DisplayMainMenu();
    void DisplayPlayStartMenu();
    void Quit();
    void GenerateEnemyCars();
    void UpdateEnemyCars();
    void DrawEnemyCars();
    void EraseEnemyCars();
    bool IsCollide();
};
