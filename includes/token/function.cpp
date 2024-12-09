
#include "function.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

double Function::evaluate(double x)
{
    if (_func == "sin")
    {
        return sin(x);
    }
    else if (_func == "cos")
    {
        return cos(x);
    }
    else if (_func == "tan")
    {
        return tan(x);
    }
    else if (_func == "log" || _func == "ln")
    {
        return log(x);
    }
    else if (_func == "sqrt")
    {
        return sqrt(x);
    }
    else if (_func == "e")
    {
        return exp(x);
    }
    else if (_func == "asin")
    {
        return asin(x);
    }
    else if (_func == "acos")
    {
        return acos(x);
    }
    else if (_func == "atan")
    {
        return atan(x);
    }
    else if (_func == "sinh")
    {
        return sinh(x);
    }
    else if (_func == "cosh")
    {
        return cosh(x);
    }
    else if (_func == "tanh")
    {
        return tanh(x);
    }
}