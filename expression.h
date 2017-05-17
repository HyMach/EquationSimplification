/*
 * expression.h
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include<vector>
#include"term.h"
#include<iostream>
#ifndef EXPRESSION_H_
#define EXPRESSION_H_

class Expression
{
private:

	char optType;  // the type of operator
	int optPrec;   // the  precedence of operator
	bool opt;      // to present whether it is an operator or not
	double numValue; //
	bool numconst;  //
    bool operant;
public:
std::vector<Term> terms;

		Expression()
{
			optType = 'n';
			optPrec = -1;
			opt = false;
			numValue = 0.0;
			numconst = false;
			operant = false;
}
		Expression(char c);
		Expression(const std::string& str);
		Expression(const Var& v);
		Expression(const Term& t);
		Expression(const Expression& expr);
		Expression(const double num);
		~Expression();
		Expression operator+(const Expression& expr) const;
		Expression operator^(const Expression& expr) const;
		Expression operator-(const Expression& expr) const;
		Expression operator*(const Expression& expr) const;
		void operator=(const Expression& expr);
		friend Expression operator-(const Expression& expr) ;
		friend Expression operator+(const Expression& expr) ;
		void signset();
		void Orderring();
        double getNumVal()
        {
        	return numValue;
        }
		bool isOperant()
		{
			return operant;
		}
		bool isNumber()
		{
			return numconst;
		}

        char getOptType() const
        {
        	return optType;
        }
        int getOptPrec() const
        {
        	return optPrec;
        }

};

//friend Expression operator*(const Var& v1, const Expression exprs) const;
//friend Expression operator*(const Term& t1, const Expression exprs) const;
//friend Expression operator-(const Expression& expr) const;
//friend Expression operator+(const Expression& expr) const;
#endif /* EXPRESSION_H_ */
