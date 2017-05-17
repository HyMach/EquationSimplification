/*
 * term.cpp
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include"term.h"
#include<cmath>
#include <sstream>
using namespace std;
template <typename T> string tostr(const T& t) {
   std::ostringstream os;
   os<<t;
   std::string s(os.str());
   return s;
};





Term::Term()
	    {
	    	coefficient = 0.0;
	    	orders = 0;
	    	vector<Var> temp;
	    	Var Vtemp = Var();
	    	temp.push_back(Vtemp);
	    	variables = temp;
	    	numconst = false;
	    	numval = 0.0;
	    	symterms = false;
	    }


Term::Term(const Term& t1)
{
	coefficient = t1.coefficient;
	variables = t1.variables;
	orders = t1.orders;
	numconst = t1.numconst;
	numval = t1.numval;
	symterms = t1.symterms;
}



Term::Term(const Var& v)
{
	coefficient = 1.0;
	orders = v.getExpt();
	vector<Var> temp;
	temp.push_back(v);
	variables = temp;
	numconst = false;
	numval = 0.0;
	symterms = true;
}

Term::Term(const string & str)
{
	coefficient = 1.0;
	orders = 1;
	numconst = false;
	numval = 0.0;
	symterms = true;
	Var v(str);
	variables.clear();
	variables.push_back(v);
}

Term::Term(double num)
{
	coefficient = num;
	orders = 1.0;
	numconst = true;
	numval = num;
	symterms = false;
	variables.clear();

}



Term::~Term()
{

}

void Term::setTerm(const double coe, const vector<Var>& vars, const int ord)
{
	coefficient = coe;
	variables = vars;
	orders = ord;
}

Term Term::operator *(const Term& t2) const
{
	if(this->symterms == true)
	{
		if(t2.Sysmterms() == true)
		{
			Term mul = t2;
			mul.coefficient *= coefficient;
			mul.numval *= numval;
			mul.orders +=orders;
			int Nthis = variables.size();
			int N2 = mul.variables.size();
			for(int i = 0; i < Nthis; i++)
			{  bool sameVar = false;
				for(int j = 0; j < N2; j++)
				{
					if(variables[i].getVarName() == mul.variables[j].getVarName())
					{
						mul.variables[j].setExpt(variables[i].getExpt() + mul.variables[j].getExpt() );
						sameVar = true;
						break;
					}

				}
				if(!sameVar)
				{
					mul.variables.push_back(variables[i]);
				}
			}
		//	mul.variables.insert(mul.variables.end(), variables.begin(), variables.end());
			mul.Orderring();

			return mul;
		}
		else //if(t2.Sysmterms() == false && t2.isNumconst() == true)
		{
			Term mul(*this);
			mul.setCoeff(coefficient*t2.getCoeff());
			mul.Orderring();
			return mul;
		}
	}
	else
	{
		Term mul(t2);
	mul.setCoeff(coefficient*t2.getCoeff());
	mul.Orderring();
	return mul;
	}
}

Term Term::operator *(const Var& v) const
{
	Term mul = *this;
	mul.orders += v.getExpt();
	mul.variables.push_back(v);
	mul.Orderring();
	return mul;
}

Term Term::operator ^(int pn) const
{
	Term t(*this);
   t.coefficient = pow(coefficient, pn);


	t.numval = numval*pn;
	if(t.Sysmterms() == true) t.orders = (t.orders)*pn;
	int Ns = t.variables.size();
	for(int i = 0; i < Ns; i++)
	{   t.variables[i].setExpt(variables[i].getExpt()*pn);
		//t.variables[i].expt *= pn;
	}
	t.Orderring();
	return t;
}

void Term::operator =(const Term & t2)
{
	coefficient = t2.coefficient;
	variables = t2.variables;
	orders = t2.orders;
	numconst= t2.numconst;
	 numval=t2.numval;
	symterms=t2.symterms;

}

void Term::operator =(const Var & v)
{
	coefficient = 1.0;
	variables.clear();
	variables.push_back(v);
	orders = v.getExpt();
	numconst = false;
	numval = 0.0;
	symterms = true;
}

bool Term::operator ==(Term t2)    // everything is the same except the coefficient
				{
	Orderring();
	t2.Orderring();
	if(numconst == true && t2.numconst == true) return true;
	int N1 = variables.size();
	int N2 = t2.variables.size();
	if(N1 != N2) return false;
	else if(orders != t2.orders) return false;
	else
	{
		for(int i = 0; i < N1; i++)
		{
			if(!(variables[i] == t2.variables[i])) return false;
		}
		return true;
	}
	return false;
				}


bool Term::operator <(Term t2)
{
	Orderring();
	t2.Orderring();
   if(numconst == true)
   {
	   if(t2.numconst == true) return false;
	  		   else return true;
   }
   else if (t2.numconst == false)
   {

	   if(orders < t2.orders) return true;
	   else if( orders > t2.orders) return false;
	   else
	   {
		   int Ns = min(variables.size(), t2.variables.size());
		   for(int i = 0; i < Ns; i++)
		   {
			   if((variables[i] < t2.variables[i])) return true;
			   else if ((variables[i] == t2.variables[i])) continue;
			   else return false;
		   }
		   if(variables.size() > t2.variables.size()) return true;
		   else return false;
	   }
   }
   else return false;
}

bool Term::operator >(Term  t2)
{
	Orderring();
	t2.Orderring();

	if(numconst == true)
	   {
		  return false;
	   }
	else if (t2.numconst == false)
	{

		if(orders > t2.orders) return true;
		else if( orders < t2.orders) return false;
		else
		{
			int Ns = min(variables.size(), t2.variables.size());
			for(int i = 0; i < Ns; i++)
			{
				if(!(variables[i] > t2.variables[i])) return false;
			}
			return true;
		}
	}
	else return false;
}


void Term::calOrders()
{
	int Ns = variables.size();
	orders = 0;
	for(int i = 0; i < Ns; i++)
	{
		orders += variables[i].getExpt();
	}


}


void Term::Orderring()
{

	calOrders();
	int Ns = variables.size();

	//  implement insertion sort
	for(int i = 1; i < Ns; i++)
	{

		Var key= variables[i];

		int j = i -1;
		while(j >=0 && variables[j] < key)
		{
			variables[j+1]= variables[j];

			j = j-1;
		}
		variables[j+1] = key;

	}
	// merge the like terms

	for(int i = 1; i < Ns; i++)
	{
		if(variables[i].getVarName() == variables[i-1].getVarName())
		{
			variables[i-1].setExpt( variables[i-1].getExpt() +  variables[i].getExpt());

			variables.erase(variables.begin() + i);
			Ns--;
			i--;
			if(variables[i].getExpt() == 0)
			{
				variables.erase(variables.begin() + i);
				Ns--;
				i--;
			}
		}
	}
	 Ns = variables.size();
	for(int i = 0; i < Ns; i++)
	{
		if(variables[i].getExpt() == 0)
		{
			if(Ns > 1)
			{
			variables.erase(variables.begin() + i);
			Ns--;
			i--;
			}
			else
			{
				this->numconst = true;
				this->numval = this->coefficient;
				this->symterms = false;
				this->variables.clear();
			}
		}
	}

}

string Term::outstrsign() const
{
	   string outs;
           outs +=" ";
           if(coefficient > 0)
           { outs += "+";
           if(abs(abs(coefficient)-1) > 1.e-12 || numconst == true ) outs += tostr(coefficient);
           }
           else
        	   { outs +='-';
        	   if(abs(abs(coefficient)-1) > 1.e-12 || numconst == true) outs += tostr(abs(coefficient));
        	   }
		   int Ns = variables.size();
		   for(int i =0; i < Ns; i++)
		   {
			   outs += "(";
			   outs += variables[i].getVarName();
			   outs += ")";
			   if(variables[i].getExpt() != 1)
			   {
				   outs +="^";
				  // outs += "(";
				   outs += tostr(variables[i].getExpt());
				  // outs += ")";

			   }
			   if(i < Ns -1) outs += "*";
		   }

    return outs;

}

string Term::outstrHeadsign() const
{
	 string outs;
	        //   outs +=' ';
	           if(coefficient > 0)
	           {// outs += '+';
	           if(abs(abs(coefficient)-1) > 1.e-12 || numconst == true) outs += tostr(coefficient);

	           }
	           else outs += tostr(coefficient);
			   int Ns = variables.size();
			   for(int i =0; i < Ns; i++)
			   {
				   outs += '(';
				   outs += variables[i].getVarName();
				   outs += ')';
				   if(variables[i].getExpt() != 1)
				   {
					   outs +='^';
					  // outs += '(';
					   outs += tostr(variables[i].getExpt());
					  // outs += ')';

				   }
				   if(i < Ns -1) outs += "*";
			   }

	    return outs;

}

