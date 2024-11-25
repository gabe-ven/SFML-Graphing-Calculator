
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
    else if (_func == "log")
    {
        return log(x);
    }
    else if (_func == "sqrt")
    {
        return sqrt(x);
    }
}