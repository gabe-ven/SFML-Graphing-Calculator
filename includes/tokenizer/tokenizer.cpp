#include "tokenizer.h"

Queue<Token *> Tokenizer::tokenize(const string &equation)
{
    Queue<Token *> infix;
    for (int i = 0; i < equation.size(); i++)
    {
        char ch = equation[i];
        if (isspace(ch)) // skip blanks
        {
            continue;
        }
        if (isdigit(ch)) // integers
        {
            infix.push(new Integer(string(1, ch)));
        }
        else if (isalpha(ch)) // chars (sin, cos, X, ...)
        {
            string func = "";
            while (i < equation.size() && isalpha(equation[i])) // get every char in the string
            {
                func += equation[i++];
            }
            i--;

            if (func == "X" || func == "x")
            {
                infix.push(new Variable(func));
            }
            else
            {
                infix.push(new Function(func));
            }
        }
        else
        {
            if (ch == '(') // left paren
            {
                infix.push(new LeftParen());
            }
            else if (ch == ')') // right paren
            {
                infix.push(new RightParen());
            }
            else // operator
            {
                infix.push(new Operator(string(1, ch)));
            }
        }
    }

    return infix;
}