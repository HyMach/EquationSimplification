/*
 * main.cpp
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include<iostream>
#include"parser.h"
#include<fstream>
#include <stdlib.h>
#include <csignal>

using namespace std;



#include <signal.h>

#include <stdio.h>
#include <unistd.h>

void my_handler(int s){
          cout<<"\n";
          cout << " The program is terminated\n";
           exit(1);

}




const bool isValibInput(const char c)
{
	if(toupper(c) <= 'Z' && 'A' <=toupper(c)) return true;
	else if('0' <= c && c <= '9' ) return true;
	else if(c == '+' || c == '-' || c == '^' || c == '*') return true;
	else if (c == '(' || c == ')') return true;
	else if (c == '=') return true;
	else if(c == '.') return true;
	else return false;
}


int main()
{

	struct sigaction sigIntHandler;

	   sigIntHandler.sa_handler = my_handler;
	   sigemptyset(&sigIntHandler.sa_mask);
	   sigIntHandler.sa_flags = 0;

cout << "\n";
cout << " This program is for expanding and simplifying polynomial equations\n" ;
cout << " All the variables should be enclosed by a pair of round brackets \n";
cout << " Multiplication is presented by '*' and cannot be omitted \n";
cout << " For negative exponent, the exponent should be enclosed by a pair of round brackets as well\n";
cout <<	" since the precedence of '^'";
cout <<	" is larger than '-'; same for multiplication\n";
cout << " One can input a file or an expression of equation\n";
cout << " A line of expression, which is an equation is ended by 'ENTER' key\n";
cout << " To Stop the input, press Ctrl + C \n";


cout << "\n" << "\n";
cout << " Please type an expression of equation or a file\n";

char co;
//co = cin.get();
while(1)
{  co = cin.get();
	sigaction(SIGINT, &sigIntHandler, NULL);
    if(co == ' ') continue;
    else if(co == 'f')
	{
		string filename;
		char c;
		while((c = cin.get()) !='\n')
					{
						if( c == ' ') continue;
						else if(c == '(') continue;
						else if(c == ')') continue;
						else if(c == '"') continue;
						else if(c == '"') continue;
						else filename += c;

						}

		std::ifstream file(filename.c_str());
		std::string temp;
		string fileout = filename+".out";
					 			std::ofstream out;
					 			out.open(fileout.c_str());
		 while(std::getline(file, temp)) {

			 string input1 = temp;

			 string input;
			 			int N1= input1.size();
			 			for(int i = 0; i < N1; i++)
			 			{
			 				if(input1[i] != ' ')	input +=input1[i];
			 			}

			 			Parser test;
			 			test.inputToExprStream(input,0);
			 			test.infixToPostfix();
			 			test.expressionEval();
			 			//test.exprOutoScreen();


			 			test.exprOutoFile(out);
			 		//	out.close();





		 }
			cout << "\n";
		 out.close();



	}
	else{

		string input1;
		if( isValibInput(co) ) input1.push_back(co);
			char c;
			while((c = cin.get()) !='\n')
			{


				if( isValibInput(c) ) input1.push_back(c);
				else continue;

				}
			string input;
			int N1= input1.size();
			for(int i = 0; i < N1; i++)
			{
				if(input1[i] != ' ')	input +=input1[i];
			}

			Parser test;
			test.inputToExprStream(input,0);
			test.infixToPostfix();
			test.expressionEval();
			test.exprOutoScreen();
			cout << "\n\n";
		}
}
return 0;


}

