#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include <iostream>
#include <iomanip>
#include "token.h"

using namespace std;

class RightParen : public Token
{
public:
    RightParen() : Token(5), _p(')') {}
    int get_type() { return 5; }
    void print() { cout << ')'; }

private:
    char _p;
};

#endif