/*
	Name: 			use point in function
	Copyright: 		pezy.me
	Author: 		pezy
	Date: 			01/07/13 16:45
	Description: 	show * and &. output 566.
*/

#include <iostream>

int nFive = 5;
int nSix  = 6;
void SetToSix(int *&pTempPtr);

using namespace std;
int main()
{
	int *pPtr = &nFive;
	cout << *pPtr;
	
	SetToSix(pPtr);
	cout << *pPtr;
	
	return 0;
} 

void SetToSix(int *&pTempPtr)
{
	pTempPtr = &nSix;
	cout << *pTempPtr;
}
