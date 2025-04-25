#include "clsLoginScreen.h"
#include <iostream>

int main()
{
	bool loginAgin = false;

	do
	{
		loginAgin = clsLoginScreen::ShowLoginScreen();

	} while (loginAgin);

	return 0;
}