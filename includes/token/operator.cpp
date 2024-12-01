#include "operator.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

double Operator::evaluate(double num1, double num2)
{
    double result;

    if (_op == '+')
    {
        result = num1 + num2;
    }
    else if (_op == '-')
    {
        result = num1 - num2;
    }
    else if (_op == '*')
    {
        result = num1 * num2;
    }
    else if (_op == '/')
    {
        result = num1 / num2;
    }
    else if (_op == '^')
    {
        result = pow(num1, num2);
    }
    return result;
}

double Operator::get_val()
{

    if (_op == '+' || _op == '-')
    {
        return 1;
    }

    else if (_op == '*' | _op == '/')
    {
        return 2;
    }
    else if (_op == '^')
    {
        return 3;
    }
}
