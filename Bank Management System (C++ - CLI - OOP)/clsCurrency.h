#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency {
private:
	enum enMode { emptyMode, updateMode };
	
	string _country;
	string _currencuCode;
	string _currencyName;
	float _rate;
	enMode _mode;

	static clsCurrency _ConvertDataLineToCurrencyObject(string dataLine) {
		vector<string> vDataLineParts = clsString::Split(dataLine, "#//#");
		return clsCurrency(enMode::updateMode, vDataLineParts[0], vDataLineParts[1], vDataLineParts[2], stof(vDataLineParts[3]));
	}

	string _ConvertCurrencyObjectToDataLine(clsCurrency& currency, string sepeator = "#//#") {
		string dataLine;

		dataLine += currency._country + sepeator;
		dataLine += currency._currencuCode + sepeator;
		dataLine += currency._currencyName + sepeator;
		dataLine += to_string(currency._rate);

		return dataLine;
	}

	static vector<clsCurrency> _LoadCurrenciesFromFile() {
		vector<clsCurrency> vCurrencies;
		fstream file;

		file.open("Currencies.txt", ios::in);

		if (file.is_open()) {
			string dataLine;

			while (getline(file, dataLine)) {
				vCurrencies.push_back(_ConvertDataLineToCurrencyObject(dataLine));
			}

			file.close();
		}

		return vCurrencies;
	}

	void _SaveCurrenciesToFile(vector<clsCurrency>& vCurrencies) {
		fstream file;

		file.open("Currencies.txt", ios::out);

		if (file.is_open()) {
			for (clsCurrency& currency : vCurrencies) {
				file << _ConvertCurrencyObjectToDataLine(currency) << endl;
			}

			file.close();
		}
	}

	void _Update() {
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile();
		fstream file;

		file.open("Currencies.txt", ios::out | ios::app);

		if (file.is_open()) {
			for (clsCurrency& currency : vCurrencies) {
				if (currency.GetCurrencyName() == this->GetCurrencyName()) {
					currency = *this;
					break;
				}
			}

			file.close();
		}

		_SaveCurrenciesToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrency() {
		return clsCurrency(enMode::emptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode mode, string country, string currencuCode, string currencyName, float rate) {
		_mode = mode;
		_country = country;
		_currencuCode = currencuCode;
		_currencyName = currencyName;
		_rate = rate;
	}

	string GetCountry() {
		return _country;
	}
	
	string GetCurrencyCode() {
		return _currencuCode;
	}

	string GetCurrencyName() {
		return _currencyName;
	}

	void UpdateRate(float rate) {
		_rate = rate;
		_Update();
	}

	float GetRate() {
		return _rate;
	}

	bool IsEmpty() {
		return (_mode == enMode::emptyMode);
	}

	static bool IsCurrencyExists(string nameOrCode) {
		return !(Find(nameOrCode).IsEmpty());
	}

	static clsCurrency Find(string nameOrCode) {
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile();
		nameOrCode = clsString::LettersToUppers(nameOrCode);

		for (clsCurrency& currency : vCurrencies) {
			if (clsString::LettersToUppers(currency._country) == nameOrCode || clsString::LettersToUppers(currency._currencuCode) == nameOrCode) {
				return currency;
			}
		}

		return _GetEmptyCurrency();
	}

	vector<clsCurrency> GetCurrenciesList() {
		return _LoadCurrenciesFromFile();
	}
	
	float ConvertToDollar(float convertingAmount) {
		return (convertingAmount / _rate);
	}

	float ConvertToAnotherCurrency(clsCurrency& currencyTo, float convertingAmount) {
		return (ConvertToDollar(convertingAmount) * currencyTo.GetRate());
	}

};