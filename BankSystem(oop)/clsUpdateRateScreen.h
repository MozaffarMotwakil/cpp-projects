#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateRateScreen : protected clsScreen {
private:
	static string _ReadCurrencyCodeOrCountry() {
		return clsInputeValidate::ReadString("\nEnter Currency code or country name: ", true);
	}

	static void _PrintCurrencyCard(clsCurrency currency) {
		cout << "\nCurrency Card:";
		cout << "\n___________________\n";
		cout << "\nCountry      : " << currency.GetCountry();
		cout << "\nCurrency Code: " << currency.GetCurrencyCode();
		cout << "\nCurrency Name: " << currency.GetCurrencyName();
		cout << "\nRate (1$)    : " << currency.GetRate();
		cout << "\n___________________\n";
	}

	static char _ConfermUpdateProcess() {
		return clsInputeValidate::ReadChar("\nAre you sure you want to update the rate of this currency ? (Y/N): ");
	}

	static float _ReadNewRate() {
		cout << "\nUpdate Currency Rate:";
		cout << "\n__________________________\n";
		return clsInputeValidate::ReadPositiveNumber("\nEnter new rate: ");
	}

public:
	static void ShowUpdateRateScreen() {
		clsScreen::DrawScreenHeder("\t     Update Date Screen");
		string currencyCodeOrCountry = _ReadCurrencyCodeOrCountry();
		clsCurrency currency = clsCurrency::Find(currencyCodeOrCountry);

		if (!currency.IsEmpty()) {
			_PrintCurrencyCard(currency);
			char answer = _ConfermUpdateProcess();
			if (answer == 'Y' || answer == 'y') {
				currency.UpdateRate(_ReadNewRate());
				cout << "\nCurrency Rate Update Seccessfuly\n";
				_PrintCurrencyCard(currency);
			}
			else {
				cout << "\nThe operation was cancelled\n";
			}
		}
		else {
			cout << "\nThe Currency Was Not Found\n";
		}
	}

};