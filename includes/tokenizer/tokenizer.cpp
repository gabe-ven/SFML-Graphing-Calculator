#include "tokenizer.h"

Queue<Token *> Tokenizer::tokenize(const string &equation)
{
    Queue<Token *> infix;
    bool unary = true;
    isInvalid = false;

    for (int i = 0; i < equation.size(); i++)
    {
        char ch = equation[i];
        if (isspace(ch)) // skip spaces
            continue;

        if (isdigit(ch)) // numbers
        {
            string num = "";
            while (i < equation.size() && (isdigit(equation[i]) || equation[i] == '.'))
            {
                num += equation[i++];
            }
            i--;

            infix.push(new Integer(num));
            unary = false;
        }
        else if (isalpha(ch)) // variables or functions
        {
            string func = "";

            if (ch == 'x' || ch == 'X')
            {
                infix.push(new Variable("X"));
                i++;

                if (i < equation.size() && equation[i] == '^')
                {
                    infix.push(new Operator("^"));
                    i++;
                    string num = "";
                    while (i < equation.size() && isdigit(equation[i]))
                    {
                        num += equation[i++];
                    }
                    i--;
                    infix.push(new Integer(num));
                }
                else if (i < equation.size() && isalpha(equation[i]))
                {
                    while (i < equation.size() && isalpha(equation[i]))
                    {
                        func += equation[i++];
                    }
                    i--;

                    infix.push(new Operator("*"));
                    infix.push(new Function(func));
                }
            }
            else
            {
                while (i < equation.size() && isalpha(equation[i]))
                {
                    func += equation[i++];
                }
                i--;

                if (func == "x" || func == "X") // var x
                {
                    infix.push(new Variable(func));
                }
                else if (func == "sin" || func == "cos" || func == "tan" || func == "log" || func == "e" || func == "ln")
                {
                    infix.push(new Function(func));
                }
                else
                {
                    isInvalid = true;
                }
            }
            unary = false;
        }

        else if (ch == '(') // left paren
        {
            infix.push(new LeftParen());
            unary = true;
        }
        else if (ch == ')') // right paren
        {
            infix.push(new RightParen());
            unary = false;
        }
        else if (ch == '+' || ch == '*' || ch == '/' || ch == '^') // operators
        {
            if (ch == '-' && unary) // unary
            {
                infix.push(new Integer("-1"));
                infix.push(new Operator("*"));
            }
            else
            {
                infix.push(new Operator(string(1, ch)));
            }
            unary = false;
        }
    }

    return infix;
}
