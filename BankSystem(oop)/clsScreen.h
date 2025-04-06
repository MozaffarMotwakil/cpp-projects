#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:
	static void DrawScreenHeder(string tital, string subTital = "") {
		cout << "\n\t\t\t\t\t___________________________________________";
		cout << "\n\n\t\t\t\t\t" << tital;

		if (subTital != "") {
			cout << "\n\t\t\t\t\t" << subTital;
		}

		cout << "\n\t\t\t\t\t___________________________________________\n";

		cout << "\n\t\t\t\t\tUser: " << currentUser.userName;
		cout << "\n\t\t\t\t\tDate: " << clsDate::DateToString(clsDate::LocalDate()) << "\n\n";
	}

	static bool CheckAccessRight(clsUser::enPermitions permission) {
		if (!currentUser.HasPermission(permission)) {
			DrawScreenHeder("     Access Denied Contact Your Admin");
			return false;
		}
		else {
			return true;
		}
	}
};

