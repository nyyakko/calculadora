#include "calc/Calc.hpp"

int main()
{
    static auto constexpr FACTOR = 40;
    static auto constexpr WIDTH  = 9 * FACTOR;
    static auto constexpr HEIGHT = 16 * FACTOR;
    
    Calc calculator { "Calculator", WIDTH, HEIGHT };
    
    return calculator.run();
}