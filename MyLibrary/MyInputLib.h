#pragma once

#include <iostream>
#include "MyValidationLib.h"
#include <string>

using namespace std;

namespace MyInputLib {

	char ReadChar(string Message) {
		char Char;

		cout << Message;
		cin >> Char;

		return Char;
	}

	string ReadString(string Message, bool CleanBuffer = false) {
		string Text;

		cout << Message;
		getline((CleanBuffer ? cin >> ws : cin), Text);

		return Text;
	}

	auto ReadNumber(string Message) {
		auto Number = 0;

		cout << Message;
		cin >> Number;

		while (!MyValidationLib::IsNumber(cin))
		{
			cout << "Wrong input, please enter only a number." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> Number;
		}

		return Number;
	}

	auto ReadPositiveNumber(string Message) {
		auto Number = 0;

		do
		{
			Number = ReadNumber(Message);

			if (!MyValidationLib::IsPositiveNumber(Number))
				cout << "Wrong number, please enter a positive number." << endl;

		} while (!MyValidationLib::IsPositiveNumber(Number));

		return Number;
	}

	int ReadNegativeNumber(string Message) {
		int Number = -1;

		do
		{
			cout << Message;
			Number = ReadNumber(Message);

			if (!MyValidationLib::IsNegativeNumber(Number))
				cout << "Wrong number, please enter a negative number." << endl;

		} while (!MyValidationLib::IsNegativeNumber(Number));

		return Number;
	}

	int ReadPositiveNumberInRange(int From, int To, string Message) {
		int PositiveNumber = 0;

		do
		{
			PositiveNumber = ReadPositiveNumber(Message);

			if (!MyValidationLib::IsNumberInRange(PositiveNumber, From, To))
				cout << "Wrong number, please enter a number from " << From << " to " << To << "." << endl;

		} while (!MyValidationLib::IsNumberInRange(PositiveNumber, From, To));

		return PositiveNumber;
	}

	int ReadNegativeNumberInRange(int From, int To, string Message) {
		int NegativeNumber = 0;

		do
		{
			NegativeNumber = ReadNegativeNumber(Message);

			if (!MyValidationLib::IsNumberInRange(NegativeNumber, From, To))
				cout << "Wrong number, please enter a number from " << From << " to " << To << "." << endl;

		} while (!MyValidationLib::IsNumberInRange(NegativeNumber, From, To));

		return NegativeNumber;
	}

}