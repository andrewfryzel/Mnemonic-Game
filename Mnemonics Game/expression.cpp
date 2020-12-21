/* Credit to: https://www.geeksforgeeks.org/expression-evaluation/ */

#include "expression.h"
#include <bits/stdc++.h>
#include <string>
#include <time.h>

// Function to find precedence of
// operators.
int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

// Function to perform arithmetic operations.
/*
 *	Hot function: need to optimize this *a lot*. This is 12% of __TOTAL__
 *	runtime of the second game (level 1). That's bad.
 */
int applyOp(int a, int b, char op)
{
	int sum = a + b;
	int diff = a - b;
	int mult = a * b; /* x86 can do this in 2 cycles + 1 instr. */
	if (op == '+')
	{
		return sum;
	}
	else if (op == '-')
	{
		return diff;
	}
	else if (op == '*')
	{
		return mult;
	}
	else if (op == '/')
	{
		if ((b == 0) || (a % b))
		{
			return INT32_MIN; /* Avoid exceptions!!!!! */
		}
		return a / b;
	}
	return INT32_MIN;
}

// Function that returns value of
// expression after evaluation.
int evaluate(std::string tokens)
{
	int i;

	// stack to store integer values.
	std::stack<int> values;

	// stack to store operators.
	std::stack<char> ops;

	for (i = 0; i < tokens.length(); ++i)
	{
		char CurToken = tokens[i];
		// Current token is a whitespace,
		// skip it.
		if (CurToken == ' ')
			continue;

		// Current token is an opening
		// brace, push it to 'ops'
		else if (CurToken == '(')
		{
			ops.push(CurToken);
		}

		// Current token is a number, push
		// it to stack for numbers.
		else if (isdigit(CurToken))
		{
			int val = 0;

			// There may be more than one
			// digits in number.
			while (i < tokens.length() && isdigit(CurToken))
			{
				val = (val * 10) + (CurToken - '0');
				CurToken = tokens[++i];
			}

			values.push(val);
		}

		// Closing brace encountered, solve
		// entire brace.
		else if (CurToken == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				/* This function is a hot spot. Do this so
				 * pipeline's happy. */
				char op = ops.top();
				ops.pop();

				int val1 = values.top();
				values.pop();

				values.push(applyOp(val1, val2, op));
			}

			// pop opening brace.
			if (!ops.empty())
				ops.pop();
		}

		// Current token is an operator.
		else
		{
			// While top of 'ops' has same or greater
			// precedence to current token, which
			// is an operator. Apply operator on top
			// of 'ops' to top two elements in values stack.
			while (!ops.empty() &&
			       precedence(ops.top()) >= precedence(CurToken))
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			// Push current token to 'ops'.
			ops.push(CurToken);
		}
	}

	// Entire expression has been parsed at this
	// point, apply remaining ops to remaining
	// values.
	while (!ops.empty())
	{
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	// Top of 'values' contains result, return it.
	return values.top();
}

std::string randomExpression(int par, int rngA, int rngB, int rngC)
{
	srand(time(0));

	std::string toRet = "";
	toRet.append(std::to_string((rand() % 6) + 1));

	par = par % 2;

	switch (rngA % 4)
	{
	case 0:
		toRet.append(" + ");
		break;
	case 1:
		toRet.append(" - ");
		break;
	case 2:
		toRet.append(" * ");
		break;
	case 3:
		toRet.append(" / ");
		break;
	}
	if (par)
		toRet.append("( ");

	toRet.append(std::to_string((rand() % 10) + 1));

	switch (rngB % 4)
	{
	case 0:
		toRet.append(" + ");
		break;
	case 1:
		toRet.append(" - ");
		break;
	case 2:
		toRet.append(" * ");
		break;
	case 3:
		toRet.append(" / ");
		break;
	}

	toRet.append(std::to_string((rand() % 10) + 1));

	if (par)
		toRet.append(" )");

	switch (rngC % 4)
	{
	case 0:
		toRet.append(" + ");
		break;
	case 1:
		toRet.append(" - ");
		break;
	case 2:
		toRet.append(" * ");
		break;
	case 3:
		toRet.append(" / ");
		break;
	}

	toRet.append(std::to_string((rand() % 5) + 1));
	return toRet;
}

std::string randomCheckedIntegerExpression(int &val)
{
	std::string expr = "(0+0)/(2/0)";
	int Values[4];
	for (int Idx = 0; Idx < 4; ++Idx)
	{
		Values[Idx] = rand();
	}

	/* Prevent division by 0. */
	for (;;)
	{
		/* Value is set to be ridiculously negative if 0.
		 * That, however, can be made positive with something
		 * like 0 - MIN_INT
		 * That's not good, so terminate this way.
		 */
		int32_t Eval = static_cast<int32_t>(evaluate(expr));
		if (abs(Eval) < 16384)
		{
			break;
		}
		srand(time(0));
		expr = randomExpression(rand(), rand(), rand(), rand());
	}
	val = evaluate(expr);
	std::cout << "Evaluate: " << evaluate(expr) << std::endl;
	return expr;
}
