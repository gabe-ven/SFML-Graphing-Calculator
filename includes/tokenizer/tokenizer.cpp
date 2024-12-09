#include "tokenizer.h"

Queue<Token *> Tokenizer::tokenize(const string &equation)
{
    Queue<Token *> infix;
    bool unary = true; // flag for unary
    isInvalid = false; // flag for invalid functions

    for (int i = 0; i < equation.size(); i++)
    {
        char ch = equation[i];
        if (isspace(ch)) // skip spaces
            continue;

        if (isdigit(ch)) // numbers
        {
            string num = "";
            // append all numbers
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

                if (i < equation.size() && equation[i] == '^') // check for exponent AFTER x
                {
                    infix.push(new Operator("^"));
                    i++;
                    string num = "";
                    // collect numbers for the exponent
                    while (i < equation.size() && isdigit(equation[i]))
                    {
                        num += equation[i++];
                    }
                    i--;
                    infix.push(new Integer(num));
                }
                else if (i < equation.size() && isalpha(equation[i]))
                {
                    // handle stuff like x * x and xsin(x)
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
                // collect functions like sin, cos
                while (i < equation.size() && isalpha(equation[i]))
                {
                    func += equation[i++];
                }
                i--;

                if (func == "x" || func == "X") // var x
                {
                    infix.push(new Variable(func));
                }
                else if (func == "sin" ||  // sin
                         func == "cos" ||  // cos
                         func == "tan" ||  // tan
                         func == "log" ||  // log
                         func == "e" ||    // e
                         func == "ln" ||   // ln
                         func == "asin" || // asin
                         func == "acos" || // acos
                         func == "atan" || // atan
                         func == "sinh" || // sinh
                         func == "cosh" || // cosh
                         func == "tanh")   // tanh
                {
                    if (i + 1 < equation.size() && equation[i + 1] == '(') // check if function is followed by paren
                    {
                        infix.push(new Function(func));
                    }

                    else // dont add a function if there are no parentheses
                    {
                        isInvalid = true;
                    }
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
            if (i == 0 || equation[i - 1] == '(')
            {
                isInvalid = true;
            }
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
