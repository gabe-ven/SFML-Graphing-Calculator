#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <iomanip>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/function.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/variable.h"

using namespace std;

class RPN
{
public:
    RPN() {}
    RPN(Queue<Token *> input_q) : input(input_q) {}

    double operator()() { return rpn(input); }

    double operator()(double num);

    double rpn(Queue<Token *> input_q);

    void set_input(Queue<Token *> input_q);

private:
    Queue<Token *> input;
};

#endif