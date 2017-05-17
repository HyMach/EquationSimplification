/*
 * var.cpp
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include"var.h"

Var::Var(string n, int pn )
{
	name = n;
	expt = pn;
}
Var::Var(const Var& var)
{
	name = var.name;
	expt = var.expt;
}
Var::Var()
{
name = '0';
expt = 0;
}

Var::~Var()
{

}

int Var::getExpt() const
{
	return expt;
}

string Var::getVarName() const
{
	return name;
}

void Var::setExpt(const int pn)
{
	expt=pn;
}

void Var::setName(const string n)
{  name = n;
}

void Var::setVar(const string n, const int pn)
{
	name = n;
	expt = pn;
}

bool Var::operator>(const Var& v2) const
{
	if(expt > v2.expt) return true;
	else if(expt < v2.expt) return false;
	else {

		if(name.compare(v2.name) < 0) return true;
		else return false;

	}
}

bool Var::operator==(const Var& v2) const
				{
	if ( expt == v2.expt && name.compare(v2.name) == 0) return true;
	else return false;

				}
bool Var::operator<(const Var& v2) const
{
	if(expt < v2.expt) return true;
	else if(expt > v2.expt) return false;
	else {

		if(name.compare(v2.name) > 0) return true;
		else return false;

	}
}

void Var::operator=(const Var& v2)
{
	name = v2.name;
	expt = v2.expt;
}

Var Var::operator ^(int pn) const
{    Var v = *this;

	v.expt *= pn;
    return v;
}

