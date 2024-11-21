#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>

using namespace std;

class Token
{
public:
    Token(int type) : _type(type) {}
    virtual int get_type() { return _type; }
    virtual double get_val() { return 0; }
    virtual double evaluate(double num1, double num2) { return 0; }
    virtual void print(ostream &os)
    {
        os << "token";
    }

private:
    int _type;
};

#endif