#pragma once
#include <iostream>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h" 
#include <string>

using namespace std;

class clsBankClient : public clsPerson
{
	enum enMode { emptyMode, updateMode, newClient };

private:
	string _accountNumber;
	string _pinCode;
	float _accountBalance;
	enMode _mode;
	bool _markForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string line) {
		vector<string> vLines = clsString::Split(line, "#//#");

		return clsBankClient(enMode::updateMode, vLines[0], vLines[1], vLines[2], vLines[3], vLines[4], clsUtil::DecryptText(vLines[5]), stof(vLines[6]));
	}

	string _ConvertClientObjectToLine(clsBankClient& client, string seperator = "#//#") {
		string dataLine;

		dataLine += client.firstName + seperator;
		dataLine += client.lastName + seperator;
		dataLine += client.email + seperator;
		dataLine += client.phone + seperator;
		dataLine += client.accountNumber + seperator;
		dataLine += clsUtil::EncryptText(client.pinCode) + seperator;
		dataLine += to_string(client.accountBalance);

		return dataLine;
	}

	static clsBankClient _GetEmptyClient() {
		return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsFromFile(string filePath) {
		vector<clsBankClient> vClients;
		fstream file;

		file.open(filePath, ios::in); // read mode

		if (file.is_open())
		{
			string dataLine;

			while (getline(file, dataLine))
			{
				vClients.push_back(_ConvertLineToClientObject(dataLine));
			}

			file.close();
		}

		return vClients;
	}

	void _SaveClientsToFile(vector<clsBankClient>& vClients, string filePath) {
		fstream file;

		file.open(filePath, ios::out); // overrite mode
		
		if (file.is_open())
		{
			for (clsBankClient& client : vClients) {
				if (client._markForDelete == false) {
					file << _ConvertClientObjectToLine(client) << endl;
				}
			}

			file.close();
		}
	}

	void _Update() {
		vector<clsBankClient> vClients = _LoadClientsFromFile("Clients.txt");

		for (clsBankClient& client : vClients) {
			if (client.accountNumber == this->_accountNumber)
			{
				client = *this;
				break;
			}
		}

		_SaveClientsToFile(vClients, "Clients.txt");
	}

	void _SaveClientToFile(string filePath) {
		fstream file;

		file.open(filePath, ios::out | ios::app);

		if (file.is_open()) {
			file << _ConvertClientObjectToLine(*this) << endl;
			file.close();
		}
	}

	void _AddNew() {
		_SaveClientToFile("Clients.txt");
	}

public:
	clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string accountNumber, string pinCode, float accountBalance)
		: clsPerson(firstName, lastName, email, phone) {
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = accountBalance;
		_mode = mode;
	}

	// The accountNumber is read-only, because that we don't create a Ser property for it
	string GetAccountNumber() {
		return _accountNumber;
	}

	__declspec(property(get = GetAccountNumber)) string accountNumber;

	void SetPinCode(string pinCode) {
		_pinCode = pinCode;
	}

	string GetPinCode() {
		return _pinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string pinCode;

	void SetAccountBalance(float accountBalance) {
		_accountBalance = accountBalance;
	}

	float GetAccountBalance() {
		return _accountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float accountBalance;

	void SetMode(enMode mode) {
		_mode = mode;
	}

	enMode GetMode() {
		return _mode;
	}

	__declspec(property(get = GetMode, put = SetMode)) enMode mode;

	static clsBankClient Find(string accountNumber) {
		fstream file;

		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsBankClient client = _ConvertLineToClientObject(line);
				if (client.accountNumber == accountNumber)
				{
					file.close();
					return client;
				}
			}
		}

		return _GetEmptyClient();
	}

	static clsBankClient Find(string accountNumber, string pinCode) {
		fstream file;

		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsBankClient client = _ConvertLineToClientObject(line);
				if (client.accountNumber == accountNumber && client.pinCode == pinCode)
				{
					file.close();
					return client;
				}
			}

			file.close();
		}

		return _GetEmptyClient();
	}

	static bool IsClientExist(string accountNumber) {
		return !Find(accountNumber).IsEmpty();
	}

	bool IsEmpty() {
		return (_mode == enMode::emptyMode);
	}

	enum enSaveResult { SaveSecceeded, SaveFaildEmptObject, SaveFaildExistClient };

	enSaveResult Save() {
		switch (_mode)
		{
		case clsBankClient::emptyMode:
			return enSaveResult::SaveFaildEmptObject;
		case clsBankClient::updateMode:
			_Update();
			return enSaveResult::SaveSecceeded;
		case clsBankClient::newClient:
			if (IsClientExist(_accountNumber))
			{
				return enSaveResult::SaveFaildEmptObject;
			} else {
				_AddNew();
				return enSaveResult::SaveSecceeded;
			}
		}
	}

	static clsBankClient GetNewClientObject(string accountNumber) {
		return clsBankClient(enMode::newClient, "", "", "", "", accountNumber, "", 0);
	}

	bool Delete() {
		vector<clsBankClient> vClients = _LoadClientsFromFile("Clients.txt");

		for (clsBankClient& client : vClients) {
			if (client.accountNumber == this->accountNumber) {
				client._markForDelete = true;
				break;
			}
		}

		_SaveClientsToFile(vClients, "Clients.txt");
		*this = _GetEmptyClient();
		
		return true;
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsFromFile("Clients.txt");
	}

	static float GetTotalBalances() {
		vector<clsBankClient> vClients = _LoadClientsFromFile("Clients.txt");
		float totalBalances = 0;

		for (clsBankClient& client : vClients) {
			totalBalances += client.accountBalance;
		}

		return totalBalances;
	}

	void Deposit(float amount) {
		accountBalance += amount;
		Save();
	}
	
	bool Withdraw(float amount) {
		if (amount > accountBalance) {
			return false;
		} else {
			accountBalance -= amount;
			Save();
			return true;
		}
	}

	bool Transfer(float transferAmount, clsBankClient& destinationClient) {
		if (!Withdraw(transferAmount)) {
			return false;
		}
		else {
			destinationClient.Deposit(transferAmount);
			return true;
		}
	}

};