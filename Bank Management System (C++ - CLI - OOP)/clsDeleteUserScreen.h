#pragma once
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include <iostream>

using namespace std;

class clsDeleteUserScreen : protected clsScreen {
private:
	static void _PrintUser(clsUser& user) {
		cout << "\nClient Info:\n";
		cout << "___________________________\n";
		cout << "First name : " << user.firstName << endl;
		cout << "Last name  : " << user.lastName << endl;
		cout << "Full name  : " << user.GetFullName() << endl;
		cout << "Email      : " << user.email << endl;
		cout << "Phone      : " << user.phone << endl;
		cout << "User name  : " << user.userName << endl;
		cout << "Password   : " << user.password << endl;
		cout << "Permissions: " << user.permissions << endl;
		cout << "___________________________\n";
	}

public:
	static void ShowDeleteUserScreen() {
		string tital = "\t\tDelete Screen";

		clsScreen::DrawScreenHeder(tital);

		string userName = clsInputeValidate::ReadString("\nEnter Username: ", true);

		while (!clsUser::IsUserExist(userName)) {
			userName = clsInputeValidate::ReadString("The user isn't exists, please enter another one: ");
		}

		clsUser user = clsUser::Find(userName);
		_PrintUser(user);

		char answer = clsInputeValidate::ReadChar("Are you sure want to delete this user ? (Y/N) : ");

		if (answer == 'y' || answer == 'Y') {
			if (user.Delete()) {
				cout << "\nDelete Seccessfuly\n";
				_PrintUser(user);
			}
			else {
				cout << "\nError, Delete is faild\n";
			}
		}
	}

};