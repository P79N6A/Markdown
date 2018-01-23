//write.cpp -- using cout.write()

#include <iostream>
using namespace std;

#include <cstring> //or else string.h

int main()
{

	const char * state1 = "Florida";
	const char * state2 = "Kansas";
	const char * state3 = "Euphoria";

	int len = strlen(state2);

	cout << "Incrasing loop index:\n";

	int i;
	for(i = 1; i <= len; i++)
	{
	
		cout.write(state2, i);
		cout << "\n";
	
	}

	//concatenate output
	cout << "Decreasing loop index:\n";
	for(i = len; i > 0;i--)
	    cout.write(state2, i) << "\n";

	//exceed string length
	cout << "Exceeding string length:\n";
	cout.write(state2, len + 5) << "\n";



	return 0;
}
