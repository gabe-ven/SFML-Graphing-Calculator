
#include "shunting_yard.h"

Queue<Token *> ShuntingYard::postfix(Queue<Token *> input_q)
{
    // given 3 * 5
    // make 3 5 *
    // 1. put 3 in postfix queue
    // 2. put * in stack
    // 3. put 5 in postfix queue
    // now infix queue is empty
    // now bring pop operator stack and push in postfix queue
    Queue<Token *> postfix_q;
    Stack<Token *> operators;

    while (!input_q.empty())
    {
        Token *token = input_q.front();

        input_q.pop();

        if (token->get_type() == 1) // num
        {
            postfix_q.push(token);
        }
        else if (token->get_type() == 2) // op
        {

            while (!operators.empty() && operators.top()->get_val() >= token->get_val())
            {
                postfix_q.push(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
        else if (token->get_type() == 3) // func
        {
            operators.push(token);
        }
        else if (token->get_type() == 4) // left paren
        {
            operators.push(token);
        }
        else if (token->get_type() == 5) // right paren
        {
            while (!operators.empty() && operators.top()->get_type() != 4)
            {
                postfix_q.push(operators.top());
                operators.pop();
            }
            if (!operators.empty() && operators.top()->get_type() == 4)
            {
                operators.pop();
            }
        }
        else if (token->get_type() == 6)
        {
            postfix_q.push(token);
        }
    }

    while (!operators.empty())
    {
        postfix_q.push(operators.top());
        operators.pop();
    }

    return postfix_q;
}

Queue<Token *> ShuntingYard::postfix()
{
    return postfix(input);
}

void ShuntingYard::infix(Queue<Token *> input_q)
{
    input = input_q;
}
