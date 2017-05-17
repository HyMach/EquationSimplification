/*
 * parser.cpp
 *
 *  Created on: 2017-01-14
 *      Author: moon
 */

#include"parser.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>

void Parser::exprOutoScreen()
{
	Expression exprFinal = exprEval.top();
	exprFinal.Orderring();
	exprFinal.Orderring();
	exprFinal.signset();
	int Ne = exprFinal.terms.size();
	string strout = exprFinal.terms[0].outstrHeadsign();
	std::cout << strout;
	string strout2;
	for(int i = 1; i < Ne; i++)
	{
       strout2 += exprFinal.terms[i].outstrsign();
	}
	cout <<  strout2;
	cout << " = 0";
}

void Parser::exprOutoFile( std::ofstream& outofile)
{
	Expression exprFinal = exprEval.top();
	exprFinal.Orderring();
	exprFinal.signset();
	int Ne = exprFinal.terms.size();
	string strout = exprFinal.terms[0].outstrHeadsign();
	//std::cout << strout;
	string strout2;
	for(int i = 1; i < Ne; i++)
	{
       strout2 += exprFinal.terms[i].outstrsign();
	}
	//cout <<  strout2;
	strout += strout2 + " = 0";
	//cout << strout;
	outofile << strout <<endl;

	//cout << " = 0";
}





void Parser::inputToExprStream(const string & sinput, int flag)
{
	// the most tedious part ....
	// try a simple version first
//	Expression ExprTemp;
	int Ns = sinput.size();
	for(int i = 0; i < Ns; i++)
	{
		if(sinput[i] =='(')
		{
			if(sinput[i+1] == '(')
			{
				Expression ExprTemp('(');
				exprStream.push_back(ExprTemp);
			}
			else
			{
				if(sinput[i+1] == '-' && isdigit(sinput[i+2]))


				{

					string varName;
					  i++;
					  i++;

					  while(sinput[i] != ')')
					   {
						  varName += sinput[i];
						  i++;
					   }
					  double numval = strtod(varName.c_str(), NULL);
					  Expression ExprTemp(-numval);
					  exprStream.push_back(ExprTemp);

				}


			else if(toupper(sinput[i+1]) <= 'Z' && 'A' <= toupper(sinput[i+1]))
               {
            	   string varName;
            	   i++;

            	   while(sinput[i] != ')')
            	   {
            		   varName += sinput[i];
            		   i++;
            	   }
            	   Expression ExprTemp(varName);
            	   exprStream.push_back(ExprTemp);

               }
               else if(toupper(sinput[i+1]) <= '9' && '0' <= toupper(sinput[i+1]))
               {
            	   string varName;
            	   i++;

            	               	   while(sinput[i] != ')')
            	               	   {
            	               		   varName += sinput[i];
            	               		   i++;
            	               	   }
            	               	   double numval = strtod(varName.c_str(), NULL);
            	               	   Expression ExprTemp(numval);
            	               	   exprStream.push_back(ExprTemp);
               }
			}
		}

		else if(isdigit(sinput[i]))
		{

			string varName;

			while(isdigit(sinput[i]) || sinput[i] == '.')
			      {
			          varName += sinput[i];
			           i++;
			      }
			i--;
			      double numval = atof(varName.c_str());
			      Expression ExprTemp(numval);
			      exprStream.push_back(ExprTemp);
			     }

	else if(sinput[i] == ')')
		{
			Expression ExprTemp(')');
			exprStream.push_back(ExprTemp);
		}

		else if (sinput[i] == '+')
		{
			Expression ExprTemp('+');
			exprStream.push_back(ExprTemp);
		}

		else if (sinput[i] == '-')
				{
						Expression ExprTemp('-');
						exprStream.push_back(ExprTemp);

				}
		else if (sinput[i] == '*')
				{
					Expression ExprTemp('*');
					exprStream.push_back(ExprTemp);
				}
		else if (sinput[i] == '^')
				{
					Expression ExprTemp('^');
					exprStream.push_back(ExprTemp);
				}

		else if (sinput[i] == '=')
				{
					Expression ExprTemp('-');
					exprStream.push_back(ExprTemp);
					Expression ExprTemp2('(');
					exprStream.push_back(ExprTemp2);
				}
		else
		{
			continue;
		}

	}
	Expression ExprTemp(')');
	exprStream.push_back(ExprTemp);

}




void Parser::expressionEval()
{
    int Nsize = expressionPost.size();
    for(int i = 0; i < Nsize; i++)
    {
    	if(expressionPost[i].isOperant()) exprEval.push(expressionPost[i]);
    	else
    	{
    		Expression opval1 = exprEval.top();
    		exprEval.pop();
    		Expression opval2 = exprEval.top();
    		exprEval.pop();
    		switch(expressionPost[i].getOptType())
    		{
    		case '+':
    			exprEval.push(opval2+opval1);
    			break;
    		case '-':
    			exprEval.push(opval2-opval1);
    			break;
    		case '*':
    			exprEval.push(opval2*opval1);
    			break;
    		case '^':
    			exprEval.push(opval2^opval1);
    			break;
    		}

    	}
    }
}



void Parser::infixToPostfix()
{   stack<Expression> opt;
	int Ne = exprStream.size();
	for(int i = 0; i < Ne; i++)
	{
		if(exprStream[i].isOperant()) expressionPost.push_back(exprStream[i]);
		else if(exprStream[i].getOptType() == '(') opt.push(exprStream[i]);
		else if(exprStream[i].getOptType()== ')')
		{
			while(!opt.empty() && opt.top().getOptType() != '(')
			{
				expressionPost.push_back(opt.top());
				opt.pop();


			}
			if(!opt.empty()) opt.pop();

		}
		else
		{
			while(!opt.empty() && exprStream[i].getOptPrec() <= opt.top().getOptPrec())
			{
				expressionPost.push_back(opt.top());
				opt.pop();
			}
			opt.push(exprStream[i]);
		}

	}

	while(!opt.empty())
	{
		expressionPost.push_back(opt.top());
						opt.pop();
	}
}


