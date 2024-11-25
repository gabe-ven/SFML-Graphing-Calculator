#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include "token.h"

using namespace std;

class Variable : public Token
{

public:
    Variable(const string var) : Token(6), _var(var[0]) {}
    int get_type() { return 6; }
    char get_var() { return _var; }
    void print(ostream &os) { os << _var; }
    friend ostream &operator<<(ostream &os, Variable *token)
    {
        token->print(os);
        return os;
    }

private:
    char _var;
};

#endif
