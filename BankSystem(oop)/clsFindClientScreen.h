#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>

class clsFindClientScreen : public clsScreen {
private:
	static void _PrintClient(clsBankClient& client) {
		cout << "\nClient Info:\n";
		cout << "___________________________\n";
		cout << "First name: " << client.firstName << endl;
		cout << "Last name : " << client.lastName << endl;
		cout << "Full name : " << client.GetFullName() << endl;
		cout << "Email     : " << client.email << endl;
		cout << "Phone     : " << client.phone << endl;
		cout << "Account number: " << client.accountNumber << endl;
		cout << "Password  : " << client.pinCode << endl;
		cout << "Balance   : " << client.accountBalance << endl;
		cout << "___________________________\n";
	}

public:
	static void ShowFindClientScreen() {
		string tital = "\t     Find Client Screen";
		clsScreen::DrawScreenHeder(tital);

		string accountNumber = clsInputeValidate::ReadString("\nEnter an account nummber: ", true);

		while (!clsBankClient::IsClientExist(accountNumber)) {
			accountNumber = clsInputeValidate::ReadString("The client isn't exists, please enter another one: ");
		}

		clsBankClient client = clsBankClient::Find(accountNumber);

		if (!client.IsEmpty()) {
			cout << "\nClient Found:-";
		} else {
			cout << "\nClient is not Found:-";
		}

		_PrintClient(client);
	}

};