#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <iomanip>
#include "token.h"

using namespace std;

class Operator : public Token
{
public:
    Operator(const string op) : Token(2), _op(op[0]) {}
    char get_op() { return _op; }
    int get_type() { return 2; }
    double get_val(); // return the order/weight of the operator for shunting
    double evaluate(double num1, double num2);
    void print(ostream &os) { os << _op; }
    friend ostream &operator<<(ostream &os, Operator *token)
    {
        token->print(os);
        return os;
    }

private:
    char _op;
};

#endif