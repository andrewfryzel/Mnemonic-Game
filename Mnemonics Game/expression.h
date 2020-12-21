#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

int evaluate(std::string);
int precedence(char);
int applyOp(int, int, char);
std::string randomExpression(int, int, int, int);
std::string randomCheckedIntegerExpression(int &);

#endif // EXPRESSION_H
