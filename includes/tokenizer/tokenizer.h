#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <iomanip>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/variable.h"

using namespace std;

class Tokenizer
{
public:
    Queue<Token *> tokenize(const string &equation);
};

#endif