#include "tokenizer.h"

Queue<Token *> Tokenizer::tokenize(const string &equation)
{
    Queue<Token *> infix;
    for (int i = 0; i < equation.size(); i++)
    {
        char ch = equation[i];
        if (isspace(ch))
        {
            continue;
        }
        if (isdigit(ch))
        {
            infix.push(new Integer(string(1, ch)));
        }
        else if (isalpha(ch))
        {
            string func = "";
            while (i < equation.size() && isalpha(equation[i]))
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
            if (ch == '(')
            {
                infix.push(new LeftParen());
            }
            else if (ch == ')')
            {
                infix.push(new RightParen());
            }
            else
            {
                infix.push(new Operator(string(1, ch)));
            }
        }
    }

    return infix;
}