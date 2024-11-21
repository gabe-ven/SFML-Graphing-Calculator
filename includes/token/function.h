#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include "token.h"

using namespace std;

class Function : public Token
{

public:
    Function(const string func) : Token(3), _func(func) {}
    int get_type() { return 3; }
    string get_func() { return _func; }
    void print(ostream &os) { os << _func; }
    friend ostream &operator<<(ostream &os, Function *token)
    {
        token->print(os);
        return os;
    }

private:
    string _func;
};

#endif
