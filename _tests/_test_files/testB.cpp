#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/variable.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/shunting_yard/shunting_yard.h"

#include "../../includes/queue/MyQueue.h"

using namespace std;

bool test_stub(bool debug = false)
{
  if (debug)
  {
    cout << "testB:: test-sub() entering test_sub" << endl;
  }

  Queue<Token *> infix;
  infix.push(new Function("sin"));
  infix.push(new LeftParen());
  infix.push(new Variable("X"));
  infix.push(new Operator("+"));
  infix.push(new Integer(2));
  infix.push(new RightParen());

  ShuntingYard sy(infix);
  Queue<Token *> postfix = sy.postfix();
  RPN rpn(postfix);
  cout << "sin(x + 2)  X = 2" << rpn(2) << endl;

  return true;
}

TEST(TEST_STUB, TestStub)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
