/*
	Name: 			limits.cpp
	Copyright: 		pezy.me
	Author: 		pezy
	Date: 			29/06/13 15:10
	Description: 	show all type's size
*/

#include <iostream>
#include <limits>
#include <string.h>
using namespace std;
int main()
{
	cout << "char		is " << sizeof(char) << "bytes." << endl;
	cout << "wchar_t		is " << sizeof(wchar_t) << "bytes." << endl;
	cout << "short		is " << sizeof(short) << "bytes." << endl;
	cout << "int		is " << sizeof(int) << "bytes." << endl;
	cout << "long		is " << sizeof(long) << "bytes." << endl;
	cout << "bool		is " << sizeof(bool) << "bytes." << endl;
  	cout << "float		is " << sizeof(float) << "bytes." << endl;
  	cout << "double		is " << sizeof(double) << "bytes." << endl;
  	cout << "long double	is " << sizeof(long double) << "bytes." << endl;
	cout << endl;
	
	cout << "Maximum values:" << endl;
	cout << "short:		" << numeric_limits<short>::max() << endl;
	cout << "unsigned short:	" << numeric_limits<unsigned short>::max() << endl;
	cout << "int:		" << numeric_limits<int>::max() << endl;
	cout << "unsigned int:	" << numeric_limits<unsigned int>::max() << endl;
	cout << "long:		" << numeric_limits<long>::max() << endl;
	cout << "unsigned long:	" << numeric_limits<unsigned long>::max() << endl;
	cout << endl;
	
	cout << "Minimum int values = " << numeric_limits<int>::min() << endl;
	
	return 0;
}
