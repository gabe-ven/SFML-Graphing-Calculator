#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <iomanip>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/operator.h"

using namespace std;

class ShuntingYard
{
public:
    ShuntingYard() {}
    ShuntingYard(Queue<Token *> input_q) { input = input_q; }

    Queue<Token *> postfix();
    Queue<Token *> postfix(Queue<Token *> input_q);

    void infix(Queue<Token *> input_q);

private:
    Queue<Token *> input;
};

#endif