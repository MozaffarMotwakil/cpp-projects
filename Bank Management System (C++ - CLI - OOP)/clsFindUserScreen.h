#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen {
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
	static void ShowFindUserScreen() {
		string tital = "\t     Find User Screen";
		clsScreen::DrawScreenHeder(tital);

		string userName = clsInputeValidate::ReadString("\nEnter Username: ", true);

		while (!clsUser::IsUserExist(userName)) {
			userName = clsInputeValidate::ReadString("The user isn't exists, please enter another one: ");
		}

		clsUser client = clsUser::Find(userName);

		if (!client.IsEmpty()) {
			cout << "\nUser Found:-";
		} else {
			cout << "\nUser is not Found:-";
		}

		_PrintUser(client);
	}

};