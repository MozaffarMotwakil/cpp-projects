#pragma once
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsTransferHistory.h"

class clsTransferScreen : protected clsScreen {
private:
	static string _ReadAccountNumber(string message) {
		string accountNumber = clsInputeValidate::ReadString(message, true);

		while (!clsBankClient::IsClientExist(accountNumber)) {
			accountNumber = clsInputeValidate::ReadString("Sorry, client is not found please enter another account number: ");
		}

		return accountNumber;
	}

	static float _ReadTransferAmount(clsBankClient& sourceClient) {
		float transferAmount = clsInputeValidate::ReadPositiveNumber("\nEnter transfer amount: ");

		while (transferAmount > sourceClient.accountBalance) {
			transferAmount = clsInputeValidate::ReadPositiveNumber("\nAmount exceeds the avalibale balance, Enter another transfer amount: ");
		}

		return transferAmount;
	}

	static void _PrintClientCard(clsBankClient& client) {
		cout << "\nClient Card:";
		cout << "\n___________________\n";
		cout << "\nAccount Number: " << client.accountNumber;
		cout << "\nFull Name: " << client.GetFullName();
		cout << "\nBalance  : " << client.accountBalance;
		cout << "\n___________________\n";
	}

public:
	static void ShowTransferScreen() {
		clsScreen::DrawScreenHeder("\t     Transfer Screen");

		clsBankClient sourceClient = clsBankClient::Find(_ReadAccountNumber("\nEnter account number to transfer from: "));
		_PrintClientCard(sourceClient);
		
		clsBankClient destinationClient = clsBankClient::Find(_ReadAccountNumber("\nEnter account number to transfer to: "));
		_PrintClientCard(destinationClient);

		float transferAmount = _ReadTransferAmount(sourceClient);
		
		char answer = clsInputeValidate::ReadChar("\nAre you sure you want perform this transaction ? (Y/N) : ");

		if (answer == 'Y' || answer == 'y')
		{
			if (sourceClient.Transfer(transferAmount, destinationClient)) {
				clsTransferHistory::SaveTransferRecord(sourceClient, destinationClient, transferAmount);
				cout << "\nTransfer Done Seccessfuly\n";
				_PrintClientCard(sourceClient);
				_PrintClientCard(destinationClient);
			}
			else {
				cout << "\nTransfer Faild\n";
			}
		}
		else {
			cout << "\nTransaction Was Cancelled\n";
		}

	}

};