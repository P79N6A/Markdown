//limits.cpp: some integer limit
#include <iostream>
using namespace std;

#include <climits>

int main()
{

    int n_int = INT_MAX;
    short n_short = SHRT_MAX;
    long n_long = LONG_MAX;


    //get integer limit by sizeof
    cout << "int is "<<sizeof(int) << " bytes by sizeof"<<endl;
    cout << "short is "<<sizeof(short) << " bytes by sizeof"<<endl;
    cout << "long is "<<sizeof(long) << " bytes by sizeof"<<endl;

    cout << "maximum values:"<<endl;
    //get integer limit by climits
    cout << "int is " << INT_MAX << " by INT_MAX"<<endl;
    cout << "short is " << SHRT_MAX << " bytes by SHRT_MAX"<<endl;
    cout << "long is " << LONG_MAX << " bytes by LONG_MAX"<<endl;

    cout << "Minimum int value= " << INT_MIN << "\n";
    cout << "Bits per byte= " << CHAR_BIT << "\n";

    return 0;

}