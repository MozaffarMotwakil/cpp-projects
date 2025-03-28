#include "clsDate.h"
#include "clsPeriod.h"
#include <iostream>

using namespace std;

int main()
{
	clsDate date("27/5/2003");

	cout << date.DateToString() << endl;
	cout << date.CountOfDaysInDate() << endl;

	return 0;
}