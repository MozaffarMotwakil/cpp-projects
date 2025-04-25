#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>
#include "clsUser.h"

using namespace std;

class clsAddNewUsersScreen : protected clsScreen {
	
private:
	static short _ReadPermitions() {
		short Permissions = 0;

		char Answer = clsInputeValidate::ReadChar("\nDo you want to give this user full access ? (Y/N) : ");

		if (Answer == 'Y' || Answer == 'y')
		{
			Permissions = clsUser::enPermitions::AllPermitions;
		}
		else
		{
			cout << "\nDo you want to give access to :\n";

			Answer = clsInputeValidate::ReadChar("\nShow client list ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::ShowClientsListPermition : 0);

			Answer = clsInputeValidate::ReadChar("\nAdd new client ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::AddClientPermition : 0);

			Answer = clsInputeValidate::ReadChar("\nDelete client ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::DeleteClientPermition : 0);

			Answer = clsInputeValidate::ReadChar("\nUpdate client ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::UpdateClientPermition : 0);

			Answer = clsInputeValidate::ReadChar("\nFind client ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::FindClientPermition : 0);

			Answer = clsInputeValidate::ReadChar("\nTransactions ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::TransactionsPermition : 0);

			Answer = clsInputeValidate::ReadChar("\nManage users ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::ManageUsersPermition : 0);
			
			Answer = clsInputeValidate::ReadChar("\nLogin Register ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::LoginRegister : 0);
			
			Answer = clsInputeValidate::ReadChar("\nCurrency Exchange ? (Y/N) : ");
			Permissions += (Answer == 'Y' || Answer == 'y' ? clsUser::enPermitions::CurrencyExchange : 0);

		}

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& user) {
		user.firstName = clsInputeValidate::ReadString("\nEnter first name: ");
		user.lastName = clsInputeValidate::ReadString("\nEnter last name : ");
		user.email = clsInputeValidate::ReadString("\nEnter email: ");
		user.phone = clsInputeValidate::ReadString("\nEnter phone: ");
		user.password = clsInputeValidate::ReadString("\nEnter password: ");
		user.permissions = _ReadPermitions();
	}

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
	static void ShowAddNewUserScreen() {
		string tital = "\tAdd New Users Screen";

		clsScreen::DrawScreenHeder(tital);

		string userName = clsInputeValidate::ReadString("\nEnter Username : ", true);

		while (clsUser::IsUserExist(userName))
		{
			userName = clsInputeValidate::ReadString("\nUser with [" + userName + "] already exists, please enter another username : ", true);
		}

		clsUser newUser = clsUser::GetAddNewUserObject(userName);

		_ReadUserInfo(newUser);

		switch (newUser.Save()) {
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nAdded Successfuly\n";
			_PrintUser(newUser);
			break;
		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "\nAdded Faild bacuse the object is empty.\n";;
			break;
		case clsUser::enSaveResults::svFaildUserExists:
			cout << "\nAdded Faild bacuse the object is already exist.\n";;
			break;
		}

	}

};