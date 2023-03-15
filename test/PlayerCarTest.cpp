#include "pch.h"

#include "../game/src/PlayerCar.h"

TEST(PlayerCarTest, WhenInitializeThenPositionAvailable)
{
    Position expected(34, 22);
    PlayerCar playerCar(70);
    Position actual = playerCar.GetPosition();

    EXPECT_EQ(expected, actual);
}
