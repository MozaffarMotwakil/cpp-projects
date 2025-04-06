#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>

using namespace std;

class clsAddNewClientScreen : protected clsScreen {
private:
	static void _ReadClientInfo(clsBankClient& client) {
		client.firstName = clsInputeValidate::ReadString("\nEnter first name: ");
		client.lastName = clsInputeValidate::ReadString("\nEnter last name : ");
		client.email = clsInputeValidate::ReadString("\nEnter email: ");
		client.phone = clsInputeValidate::ReadString("\nEnter phone: ");
		client.pinCode = clsInputeValidate::ReadString("\nEnter pin code: ");
		client.accountBalance = clsInputeValidate::ReadPositiveNumber("\nEnter balance: ");
	}

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
	static void ShowAddNewClientScreen() {
		string tital = "\tAdd New Clients Screen";

		clsScreen::DrawScreenHeder(tital);
		string accountNumber = clsInputeValidate::ReadString("\nEnter an account nummber: ", true);

		while (clsBankClient::IsClientExist(accountNumber)) {
			accountNumber = clsInputeValidate::ReadString("The aacount number is already exist, please enter another one: ");
		}

		clsBankClient newClient = clsBankClient::GetNewClientObject(accountNumber);

		cout << "\nFill all folowing fiels:";
		_ReadClientInfo(newClient);

		switch (newClient.Save()) {
		case clsBankClient::enSaveResult::SaveSecceeded:
			cout << "\nAdded Successfult\n";
			_PrintClient(newClient);
			break;
		case clsBankClient::enSaveResult::SaveFaildEmptObject:
			cout << "\nAdded Faild bacuse the object is empty.\n";;
			break;
		case clsBankClient::enSaveResult::SaveFaildExistClient:
			cout << "\nAdded Faild bacuse the object is already exist.\n";;
			break;
		}

	}

};