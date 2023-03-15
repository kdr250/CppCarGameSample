#include "pch.h"

#include "../game/src/Game.h"

TEST(GameTest, IsContinuingTest)
{
    Game game;
    bool actual = game.IsContinuing();

    EXPECT_TRUE(actual);
}

TEST(GameTest, QuitTest)
{
    Game game;
    game.Quit();
    bool actual = game.IsContinuing();

    EXPECT_FALSE(actual);
}
