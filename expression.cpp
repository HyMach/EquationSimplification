/*
 * expression.cpp
 *
 *  Created on: 2017-01-14
 *      Author: moon
 */

#include"expression.h"
#include<iostream>
#include"term.h"
#include<cmath>


Expression::Expression(char c)
{
	if(c == '(' || c == ')')
	{
		optType = c;
		optPrec =  0;
		opt = true;
		numValue = 0.0;
		numconst = false;
		operant = false;
	}

	else if(c == '+' || c == '-')
	{
		optType = c;
		optPrec =  1;
		opt = true;
		numValue = 0.0;
		numconst = false;
		operant = false;
	}


	else if(c == '*')
	{
		optType = c;
		optPrec =  2;
		opt = true;
		numValue = 0.0;
		numconst = false;
		operant = false;
	}
	else if(c == '^')
	{
		optType = c;
		optPrec =  3;
		opt = true;
		numValue = 0.0;
		numconst = false;
		operant = false;
	}
	else {
		optType = 'n';
		optPrec = -1;
		opt = false;
		numValue = 0.0;
		numconst = false;
		operant = false;
	}
}

Expression::Expression(const std::string& str)
{
	optType = 'n';
	optPrec =  -1;
	opt = false;
	numValue = 0.0;
	numconst = false;
	operant = true;
	Term strTerm(str);
	terms.clear();
	terms.push_back(strTerm);

}
Expression::Expression(const Expression& expr)
{
	optType = expr.optType;
	optPrec = expr.optPrec;
	opt = expr.opt;
	numValue = expr.numValue;
	numconst = expr.numconst;
	operant = expr.operant;
	terms = expr.terms;

}

Expression::Expression(const Term& t)
{
	optType = 'n';
	optPrec =  -1;
	opt = false;
	numValue = 0.0;
	numconst = false;
	operant = true;
	terms.clear();
	terms.push_back(t);
}
Expression::Expression(const Var& v)
{
	optType = 'n';
	optPrec =  -1;
	opt = false;
	numValue = 0.0;
	numconst = false;
	operant = true;
	Term t(v);
	terms.clear();
	terms.push_back(t);
}
Expression::Expression(const double num)
{
	optType = 'n';
	optPrec =  -1;
	opt = false;
	numValue = num;
	numconst = true;
	operant = true;
	Term t(num);
	terms.clear();
	terms.push_back(t);
}
Expression::~Expression()
{}


Expression Expression::operator +(const Expression& expr) const
{

	if(operant == true)
	{
		if(expr.operant == true)
		{
			Expression exprTemp(*this);
			exprTemp.terms.insert(exprTemp.terms.end(), expr.terms.begin(), expr.terms.end());
			exprTemp.Orderring();
			return exprTemp;
		}
	else
	{
		Expression exprTemp(*this);
		return exprTemp;
		}
	}
		else
		{
			if(optType == '+')
			{
				Expression exprTemp = expr;
				return exprTemp;
			}
			else if(optType == '-')
			{
				Expression exprTemp = -expr;
				return exprTemp;
			}
			else
			{   Expression exprTemp(expr);
				return exprTemp;
			}
		}

}



Expression Expression::operator -(const Expression& expr) const
{
	Expression exprTemp;

	if(operant == true)
	{   if(expr.operant == true)
	{
		exprTemp = *this;
		Expression expr02 = -expr;

		exprTemp.terms.insert(exprTemp.terms.end(), expr02.terms.begin(), expr02.terms.end());
		exprTemp.Orderring();
		return exprTemp;

	}
	else
	{
		exprTemp = *this;
		return exprTemp;
	}


	}
	else if(operant == false)
	{
		if(optType == '+')
		{
			exprTemp = -expr;
			return exprTemp;
		}
		else if(optType == '-')
		{
			exprTemp = expr;
			return exprTemp;
		}
		else
		{
			return exprTemp;
		}

	}
	else
	{
		return exprTemp;
	}

}

Expression Expression::operator *(const Expression & expr) const
{  Expression exprMul;


int Nthis = terms.size();
int Nexpr = expr.terms.size();
for(int i=0; i < Nthis; i++)
{
	for(int j = 0; j < Nexpr;j++)
	{
		Expression exprTemp(terms[i]*(expr.terms[j]));
		exprMul = (exprMul+exprTemp);
		exprMul.Orderring();
	}
}
exprMul.Orderring();
return exprMul;

}

Expression Expression::operator ^(const Expression & expr) const
{
	Expression exprTemp(*this);
	int Ncount = (int) expr.numValue;
	if(terms.size() == 1 && terms[0].Sysmterms() == true)
	{
        //exprTemp.terms[0].setCoeff(pow(terms[0].getCoeff(), Ncount));
       // exprTemp.terms[0].setOrders(terms[0].getOrders()*Ncount);
		exprTemp.terms[0]=exprTemp.terms[0]^Ncount;
        return exprTemp;
	}
	for(int i = 2; i <=Ncount; i++)
	{
		exprTemp = exprTemp*(*this);
		exprTemp.Orderring();
	}
	return exprTemp;

}

void Expression::operator =(const Expression& expr)
{
	optType = expr.optType;
		optPrec = expr.optPrec;
		opt = expr.opt;
		numValue = expr.numValue;
		numconst = expr.numconst;
		operant = expr.operant;
		terms = expr.terms;


}

void Expression::signset()
{
	int Nsize = terms.size();
	if(Nsize <= 0) return ;
	if(terms[0].getCoeff() > 0) return;

	else
	{

		for(int i = 0; i < Nsize; i++)
		{
			terms[i].setCoeff(terms[i].getCoeff()*(-1));
		}

	}
}

void Expression::Orderring()
{


		int Ns = terms.size();
		if(Ns == 0) return ;
		for(int i = 0; i < Ns; i++)
		{
			if(abs(terms[i].getCoeff()) < 1.e-15)
				{ terms.erase(terms.begin() + i);
				Ns--;
				i--;
				}
		}

		//  implement insertion sort
		for(int i = 1; i < Ns; i++)
		{

			Term key= terms[i];

			int j = i -1;

			while(j >=0 && terms[j] < key)
			{
				terms[j+1]= terms[j];

				j = j-1;
			}
			terms[j+1] = key;

		}
		// merge the like terms

		for(int i = 1; i < Ns; i++)
		{
			if(terms[i] == terms[i-1])
			{
				terms[i-1].setCoeff(terms[i-1].getCoeff() + terms[i].getCoeff());
				terms[i-1].setNumVal(terms[i-1].getNumVal() + terms[i].getNumVal());

				//terms[i-1].coefficient = (terms[i-1].coefficient)*(terms[i].coefficient);
				terms.erase(terms.begin() + i);
				Ns--;
				i--;
			}
		}
}



Expression operator-(const Expression& expr)
{
	if(expr.operant == true)

	{
		Expression exprTemp;
		exprTemp = expr;
		int Nt = exprTemp.terms.size();
		for(int i=0; i < Nt; i++)
		{
			exprTemp.terms[i].setCoeff(exprTemp.terms[i].getCoeff()*(-1.0));

		}
		return exprTemp;
	}
	else if(expr.optType == '-')
	{
		Expression exprTemp('+');
		return exprTemp;
	}
	else if(expr.optType == '+')
	{
		Expression exprTemp('-');
		return exprTemp;
	}

	else {
		Expression exprTemp;
		return exprTemp;
	}
}


Expression operator+(const Expression& expr)
{ Expression exprTemp;
exprTemp = expr;
return exprTemp;
}


