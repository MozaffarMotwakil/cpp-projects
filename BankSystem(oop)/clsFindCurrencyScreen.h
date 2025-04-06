#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen {
private:
	enum enFindMethods { Code = 1, Country = 2 };

	static string _ReadCountryName() {
		return clsInputeValidate::ReadString("\nEnter the country name: ", true);
	}

	static string _ReadCurrencyCode() {
		return clsInputeValidate::ReadString("\nEnter the currency code: ", true);
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

	static void _ProccessFindOperation(string nameOrCode) {
		clsCurrency currency = clsCurrency::Find(nameOrCode);
		
		if (!currency.IsEmpty()) {
			cout << "\nCurrency Found\n";
			_PrintCurrencyCard(currency);
		}
		else {
			cout << "\nCurrency Not Found\n";
		}
	}

	static short _ReadFindMethodChoice() {
		return clsInputeValidate::ReadPositiveNumberBetween(1, 2, "\nFind By : [1] Code or [2] Country ? ");
	}

	static void _PerformFindMethod(enFindMethods choice) {
		switch (choice)
		{
		case enFindMethods::Code:
			_ProccessFindOperation(_ReadCurrencyCode());
			break;
		case enFindMethods::Country:
			_ProccessFindOperation(_ReadCountryName());
			break;
		}
	}

public:
	static void ShowFindCurrencyScreen() {
		clsScreen::DrawScreenHeder("\t   Find currency Screen");
		short choice = _ReadFindMethodChoice();
		_PerformFindMethod((enFindMethods)choice);
	}

};