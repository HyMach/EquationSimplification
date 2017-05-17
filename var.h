/*
 * var.h
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include<string>
using namespace std;
#ifndef VAR_H_
#define VAR_H_

class Var{
private:
	string name;
	int  expt;
public:
	Var(string n, int pn = 1);  // constructor
	Var(const Var& var);
    Var();
	~Var();
	bool operator == (const Var& v2) const;
	bool operator < (const Var& v2) const;
	bool operator > (const Var& v2) const;
	void operator =(const Var& v2);
	Var  operator^(int pn) const;

    string getVarName() const;
    int    getExpt() const;
    void setName(const string n);
    void setExpt(const int pn);
    void setVar(const string n, const int pn);



};



#endif /* VAR_H_ */
