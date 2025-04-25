#pragma once
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsWithdrawScreen : protected clsScreen {
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

    static string _ValidateAccountNumber() {
        string accountNumber = clsInputeValidate::ReadString("\nEnter an account nummber: ", true);

        while (!clsBankClient::IsClientExist(accountNumber)) {
            accountNumber = clsInputeValidate::ReadString("The client isn't exists, please enter another one: ");
        }

        return accountNumber;
    }

public:
    static void ShowWithdrawScreen() {
        clsScreen::DrawScreenHeder("\t\tWithdraw Screen");
        string accountNumber = _ValidateAccountNumber();

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);

        float withdrawAmount = clsInputeValidate::ReadPositiveNumber("\nEnter withdraw amount: ");

        char answer = clsInputeValidate::ReadChar("\n\nAre you sure you want perform this transactions ? (Y/N) : ");

        if (answer == 'Y' || answer == 'y')
        {
            if (client.Withdraw(withdrawAmount)) {
                cout << "\Operation Is Done Seccessfuly";
                cout << "\nNew Balance is : " << client.accountBalance << endl;
            }
            else {
                cout << "\nError: Amount Exceeds the balance";
                cout << "\nBalance can withdraw up to : " << client.accountBalance;
                cout << "\nBalance Entered : " << withdrawAmount << endl;
            }
        }
        else {
            cout << "\nOperation Was Cancelled\n";
        }
    }

};