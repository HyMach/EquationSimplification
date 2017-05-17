/*
 * term.h
 *
 *  Created on: 2017-01-12
 *      Author: moon
 */
#include<vector>
#include"var.h"
#ifndef TERM_H_
#define TERM_H_

class Term{
private:
	double coefficient;
	vector<Var> variables;
	int orders;
	bool numconst;
	double numval;
	bool symterms;
public:


	    Term();
	    Term(const Term & t1);
	    Term(const Var& v);   // set the term by one variable
	    Term(const string& str);
	    Term(const double num);
        ~Term();
        void setTerm(const double coe, const vector<Var>& vars, const int ord);
        string outstrHeadsign() const; // generate the string for output witout +/- sign
        string outstrsign() const;   // generate the string for output with +/- sign


        friend Term operator*(const Var& v1, const Term t1);
	    bool operator==( Term t2) ;
		bool operator<( Term t2);
		bool operator>(Term t2);
		Term operator*(const Term& t2) const;
		Term operator*(const Var& v) const;
		Term operator^(const int pn) const;
		void operator=( const Term& t2);
		void operator=(const Var& v);
        void Orderring();
        void AddLike(); // add like terms
        void calOrders();
        bool isNumconst() const
        {
        	return numconst;
        }


        void setOrders( int orN)
        {
        	orders = orN;
        }
        int getOrders() const
        {
        	return orders;
        }
        double getCoeff() const
        {
        	return coefficient;
        }
        void setCoeff(double num)
        {
        	coefficient = num;
        }
        void setNumVal(double num)
        {
        	numval = num;
        }
        double getNumVal() const
        {
        	return numval;
        }
        bool Sysmterms() const
        {
        	return symterms;
        }

};



#endif /* TERM_H_ */
