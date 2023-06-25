#include "calc/Calc.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #define WIN32_LEAN_AND_MEAN
    #if defined(_WIN32)
        #define WIN32
        #undef _AMD64_
        #define _X86_
    #else
        #define WIN64
        #define _AMD64_
        #undef _X86_
    #endif
#else
    #error This shit works only on Windows!
#endif

#include <minwindef.h>
#include <stdio.h>
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    static auto constexpr FACTOR = 40;
    static auto constexpr WIDTH  = 9 * FACTOR;
    static auto constexpr HEIGHT = 16 * FACTOR;
    
    Calc calculator { "Calculator", WIDTH, HEIGHT };
    
    return calculator.run();
}