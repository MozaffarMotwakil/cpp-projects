#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>

using namespace std;

class clsUpdateClientScreen : public clsScreen {
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

	static void _ReadClientInfo(clsBankClient& client) {
		client.firstName = clsInputeValidate::ReadString("\nEnter first name: ");
		client.lastName = clsInputeValidate::ReadString("\nEnter last name : ");
		client.email = clsInputeValidate::ReadString("\nEnter email: ");
		client.phone = clsInputeValidate::ReadString("\nEnter phone: ");
		client.pinCode = clsInputeValidate::ReadString("\nEnter pin code: ");
		client.accountBalance = clsInputeValidate::ReadPositiveNumber("\nEnter balance: ");
	}

public:
	static void ShowUpdateClientScreen() {
		string tital = "\t   Update client screen";

		clsScreen::DrawScreenHeder(tital);

		string accountNumber = clsInputeValidate::ReadString("\nEnter an account number: ", true);

		while (!clsBankClient::IsClientExist(accountNumber))
		{
			accountNumber = clsInputeValidate::ReadString("Sorry, client is not found please enter another one: ");
		}

		clsBankClient client = clsBankClient::Find(accountNumber);
		_PrintClient(client);

		cout << "\nUpdate Client Info:";
		cout << "\n__________________________";
		_ReadClientInfo(client);

		if (client.Save() == clsBankClient::enSaveResult::SaveSecceeded) {
			cout << "\nAccount update seccessfuly: ";
			_PrintClient(client);
		}
		else {
			cout << "\nUpdate Faild bacuse the object is empty.\n";
		}

	}

};