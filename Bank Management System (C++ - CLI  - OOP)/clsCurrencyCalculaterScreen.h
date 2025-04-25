#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsCurrencyCalculaterScreen : protected clsScreen {

private:
	static string _ReadCurrencyCodeOrCountry(string convertType) {
		string codeOrName = clsInputeValidate::ReadString("\nEnter currency code or country name to converting " + convertType + ": ", true);

		while (!clsCurrency::IsCurrencyExists(codeOrName)) {
			codeOrName = clsInputeValidate::ReadString("\nCurrency was not found, Please enter another currency code or country name to converting " + convertType + ": ", true);
		}

		return codeOrName;
	}

	static void _PrintCurrencyCard(clsCurrency& currency, string convertType) {
		cout << "\n" << convertType;
		cout << "\n___________________\n";
		cout << "\nCountry      : " << currency.GetCountry();
		cout << "\nCurrency Code: " << currency.GetCurrencyCode();
		cout << "\nCurrency Name: " << currency.GetCurrencyName();
		cout << "\nRate (1$)    : " << currency.GetRate();
		cout << "\n___________________\n";
	}

	static void _ShowConversionResult(clsCurrency& from, clsCurrency& to, float amount) {
		_PrintCurrencyCard(from, "Convert From:");
		float amountInUSD = from.ConvertToDollar(amount);
		cout << amount << " " << from.GetCurrencyCode() << " = " << amountInUSD << " USD\n";

		if (to.GetCurrencyCode() != "USD") {
			cout << "\nConverting from USD to:\n";
			_PrintCurrencyCard(to, "Convert To:");
			cout << amount << " " << from.GetCurrencyCode() << " = "
				<< from.ConvertToAnotherCurrency(to, amount) << " " << to.GetCurrencyCode() << endl;
		}
	}

public:
	static void ShowCurrencyCalculaterScreen() {
		char anotherOperation = 'N';

		do
		{
			system("cls");
			clsScreen::DrawScreenHeder("\t   Currency Calculater Screen");

			clsCurrency from = clsCurrency::Find(_ReadCurrencyCodeOrCountry("From"));
			clsCurrency to = clsCurrency::Find(_ReadCurrencyCodeOrCountry("To"));

			float amount = clsInputeValidate::ReadPositiveNumber("\nEnter the convrting amount: ");

			_ShowConversionResult(from, to, amount);

			anotherOperation = clsInputeValidate::ReadChar("\nDo you want to perform another calculation ? (Y/N): ");

		} while (anotherOperation == 'Y' || anotherOperation == 'y');

	}

};