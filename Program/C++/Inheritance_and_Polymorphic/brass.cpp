#include <iostream>
#include <cstring>
using namespace std;

#include "brass.h"

//Brass methods

Brass::Brass(const char *, long an, double bal)
{

	strncpy(fullName, s, MAX - 1);
	fullName[MAX - 1] = '\0';
	acctNum = an;
	balance = bal;

}

void Brass::Deposity(double amt)
{
	if(amt < 0)
		cout << "Negative deposit not allowed;"
			 << "deposity is cancelled.\n";
	else
		balance += amt;
}

void Brass::Withdraw(double amt)
{
	if(amt < 0)
		cout << "Negative deposity not allowed;"
			 << "withdrawal canceled.\n"; 
	else if(amt <= balance)
		balance -= amt;
	else
		cout << "Withdrawal amount of $" << amt
			 << " exceeds your balance.\n"
			 << "Withdrawal canceled.\n";
}

double Brass::Balance const
{
	return balance;
}

void Brass::Viewacct() const
{
	//set up ###.## format
	ios_base::fmtflags initialState = 
		cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.setf(ios_base::showpoint);
	cout.precision(2);
	cout << "Client:" << fullName << endl;
	cout << "Account Number:" << accNum << endl;
	cout << "Balance: $" << balance << endl;
	cout.setf(initialState); //restore originalformat
}

BrassPlus::BrassPlus(const char * s, long an, double bal,
		double ml, double r) : Brass(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r):Brass(ba)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}
