#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>

using namespace std;

class clsDeleteClientScreen : protected clsScreen {
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
	static void ShowDeleteClientScreen() {
		string tital = "\t\tDelete Screen";

		clsScreen::DrawScreenHeder(tital);

		string accountNumber = clsInputeValidate::ReadString("\nEnter an account nummber: ", true);

		while (!clsBankClient::IsClientExist(accountNumber)) {
			accountNumber = clsInputeValidate::ReadString("The client isn't exists, please enter another one: ");
		}

		clsBankClient client = clsBankClient::Find(accountNumber);
		_PrintClient(client);

		char answer = clsInputeValidate::ReadChar("Are you sure want to delete this client ? (Y/N) : ");

		if (answer == 'y' || answer == 'Y') {
			if (client.Delete()) {
				cout << "\nDelete Seccessfuly\n";
				_PrintClient(client);
			}
			else {
				cout << "\nError, Delete is faild\n";
			}
		}

	}

};