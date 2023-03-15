#include "pch.h"

#include "../game/src/PlayerCar.h"

TEST(PlayerCarTest, WhenInitializeThenPositionAvailable)
{
    Position expected(34, 22);
    PlayerCar playerCar(70);
    Position actual = playerCar.GetPosition();

    EXPECT_EQ(expected, actual);
}

TEST(PlayerCarTest, MoveTest)
{
    Position expected(38, 22);
    PlayerCar playerCar(70);
    playerCar.MoveX(4);
    Position actual = playerCar.GetPosition();

    EXPECT_EQ(expected, actual);
}

TEST(PlayerCarTest, CollideToEnemyCarTest)
{
    PlayerCar playerCar(70);
    std::unique_ptr<EnemyCar> enemyCar = std::make_unique<EnemyCar>(Position(34, 4));
    enemyCar->MoveY(18);
    bool actual = playerCar.IsCollide(enemyCar);

    EXPECT_TRUE(actual);
}
