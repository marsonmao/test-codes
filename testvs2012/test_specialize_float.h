#pragma once

#include "test_specialize.h"

template <>
class Hahaha<float>
{
public:

    int jkl;
    float sss;

    Hahaha()
        : jkl(4321)
        , sss(5.0f)
    {

    }
};