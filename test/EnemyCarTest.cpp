#include "pch.h"

#include "../game/src/EnemyCar.h"

TEST(EnemyCarTest, WhenInitializeThenPositionAvailable)
{
    Position expected(4, 4);
    EnemyCar enemycar(Position(4, 4));
    Position actual = enemycar.GetPosition();

    EXPECT_EQ(expected, actual);
}

TEST(EnemyCarTest, MoveTest)
{
    Position expected(4, 8);
    EnemyCar enemycar(Position(4, 4));
    enemycar.MoveY(4);
    Position actual = enemycar.GetPosition();

    EXPECT_EQ(expected, actual);
}

TEST(EnemyCarTest, DeadTest)
{
    EnemyCar enemycar(Position(4, 4));
    enemycar.Dead();
    bool actual = enemycar.IsDead();

    EXPECT_TRUE(actual);
}
