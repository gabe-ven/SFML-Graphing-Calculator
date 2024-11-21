#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "token.h"

using namespace std;

class Integer : public Token
{
public:
    Integer(double var) : Token(1), _var(var) {}
    Integer(const string str) : Token(1)
    {
        _var = stod(str);
    }
    double get_val() { return _var; }
    int get_type() { return 1; }
    void print(ostream &os) { os << _var; }
    friend ostream &operator<<(ostream &os, Integer *token)
    {
        token->print(os);
        return os;
    }

private:
    double _var;
};

#endif