#pragma once

class Sample
{
public:
    static int Add(int a, int b)
    {
        return a + b;
    }

    static bool IsEven(int n)
    {
        return n % 2 == 0;
    }

    static std::string Greeting()
    {
        return "Hello";
    }

    static void ThrowError()
    {
        throw("Error!");
    }
};
