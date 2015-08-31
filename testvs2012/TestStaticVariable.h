#pragma once

const int G_X = 5000;
//static const int G_X = 5000;
//extern const int G_X;

//int G_N_X = 5000;
static int G_N_X = 5000;

inline void MyMethod1() // only 1 copy through all units
{
    static int x = 1;
    std::cout << &x << std::endl;
    std::cout << G_X << std::endl;
}

static void MyMethod3() // each unit has own copy
{
    static int x = 1;
    std::cout << &x << std::endl;
    std::cout << G_X << std::endl;
}

namespace
{
void MyMethod4() // each unit has own copy
{
    static int x = 1;
    std::cout << &x << std::endl;
    std::cout << G_X << std::endl;
}
}

void SomeMethod2();

class MyClass555
{
public:
    static const int X = 10;
};