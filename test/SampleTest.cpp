#include "pch.h"

#include "../game/src/Sample.h"

TEST(SampleTest, AddMethodTest)
{
    int result = Sample::Add(1, 1);
    EXPECT_EQ(2, result);
}

TEST(SampleTest, IsEvenMethodTest)
{
    bool result = Sample::IsEven(10);
    EXPECT_TRUE(result);
}

TEST(SampleTest, GreetingMethodTest)
{
    std::string result = Sample::Greeting();
    EXPECT_EQ("Hello", result);
}

TEST(SampleTest, ThrowExceptionMethodTest)
{
    EXPECT_ANY_THROW(Sample::ThrowError());
}
