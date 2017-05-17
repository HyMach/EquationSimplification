/*
 * parser.h
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include"expression.h"
#include<string>
#include<stack>
#include<iostream>
using namespace std;
#ifndef PARSER_H_
#define PARSER_H_

class Parser
{
private:
	vector<Expression> exprStream;    // steam of expression in the original order(infix)
	vector<Expression> expressionPost; // transform the infix into postfix
	stack<Expression> exprEval;      // expression after evalu, ready to be output

public:


    void infixToPostfix();
    void expressionEval();
    void inputToExprStream(const string& sinput, int flag);
    Expression& getExpressionEval() const;
    void exprOutoScreen();
    void exprOutoFile(std::ofstream& out);
};



#endif /* PARSER_H_ */
