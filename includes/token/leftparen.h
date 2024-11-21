#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include <iostream>
#include <iomanip>
#include "token.h"

using namespace std;

class LeftParen : public Token
{
public:
    LeftParen() : Token(4), _p('(') {}
    int get_type() { return 4; }
    void print() { cout << '('; }

private:
    char _p;
};

#endif