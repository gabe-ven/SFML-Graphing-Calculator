#include "rpn.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

double RPN::operator()(double num)
{
    Queue<Token *> sub;

    while (!input.empty())
    {
        Token *token = input.front();
        input.pop();

        if (token->get_type() == 6)
        {
            sub.push(new Integer(num));
        }
        else
        {
            sub.push(token);
        }
    }

    return rpn(sub);
}

double RPN::rpn(Queue<Token *> input_q)
{
    Stack<Token *> rpn_stack;
    while (!input_q.empty())
    {
        Token *token = input_q.front();

        input_q.pop();

        if (token->get_type() == 1)
        {
            rpn_stack.push(token);
        }
        else if (token->get_type() == 2)
        {
            Token *token2 = rpn_stack.pop();
            Token *token1 = rpn_stack.pop();

            double num1 = token1->get_val();
            double num2 = token2->get_val();

            double result = token->evaluate(num1, num2);

            rpn_stack.push(new Integer(result));
        }
        else if (token->get_type() == 3)
        {
            Token *operand = rpn_stack.pop();
            double value = operand->get_val();

            Function *func = dynamic_cast<Function *>(token);
            assert(func != nullptr);
            double result = func->evaluate(value);

            rpn_stack.push(new Integer(result));
        }
    }
    Token *item = rpn_stack.pop();
    return item->get_val();
}

void RPN::set_input(Queue<Token *> input_q)
{
    input = input_q;
}
