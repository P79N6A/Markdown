//trucate.cpp -- use get() to truncate input line, if necessary

#include <iostream>
using namespace std;

const int SLEN = 10;

inline void eatline(){ while(cin.get() != '\n') continue; }

int main()
{
	
	char name[SLEN];
	char title[SLEN];

	cout << "Enter your name:";
	cin.get(name, SLEN);

	if(cin.peek() != '\n')
	{
		cout << "Sorry, we only have enough room for "
			 << name << endl;
	}

	eatline();

	cout << "Dear " << name << ", enter your title:\n";
	cin.get(title, SLEN);

	if(cin.peek() != '\n')
		cout << "We are forced to truncate your title";

	eatline();
	cout << "Name:" << name << "\nTitle:" << title << endl;

	return 0;
}