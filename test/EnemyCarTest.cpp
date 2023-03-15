#include "pch.h"

#include "../game/src/EnemyCar.h"

TEST(EnemyCarTest, WhenInitializeThenPositionAvailable)
{
    Position expected(4, 4);
    EnemyCar enemycar(Position(4, 4));
    Position actual = enemycar.GetPosition();

    EXPECT_EQ(expected, actual);
}
