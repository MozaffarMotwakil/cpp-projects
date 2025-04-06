#pragma once

#include "clsDate.h"
#include "clsPeriod.h"
#include <iostream>
#include <string>

using namespace std;

class clsInputeValidate
{
public:

	static bool IsDateBetween(clsDate DateToCheck, clsDate FirstDate, clsDate SecondDate) {
		return clsPeriod::IsDateWithinPeriod(DateToCheck, clsPeriod(FirstDate, SecondDate));
	}

	static bool IsPositiveNumber(int Number) {
		return Number >= 0;
	}

	static bool IsNegativeNumber(int Number) {
		return Number < 0;
	}

	static bool IsNumberBetween(int Number, int From, int To) {
		return (Number >= From && Number <= To);
	}

	static char ReadChar(string Message) {
		char Char;

		cout << Message;
		cin >> Char;

		return Char;
	}

	static string ReadString(string Message, bool CleanBuffer = false) {
		string Text;

		cout << Message;
		getline((CleanBuffer ? cin >> ws : cin), Text);

		return Text;
	}

	static auto ReadNumber(string Message) {
		auto Number = 0.0;

		cout << Message;
		cin >> Number;

		while (!IsNumber(cin))
		{
			cout << "Wrong input, please enter only a number." << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> Number;
		}

		return Number;
	}

	static auto ReadPositiveNumber(string Message) {
		auto Number = 0.0;

		do
		{
			Number = ReadNumber(Message);

			if (!IsPositiveNumber(Number))
				cout << "Wrong number, please enter a positive number." << endl;

		} while (!IsPositiveNumber(Number));

		return Number;
	}

	static auto ReadPositiveNumberBetween(int From, int To, string Message) {
		auto PositiveNumber = 0.0;

		do
		{
			PositiveNumber = ReadPositiveNumber(Message);

			if (!IsNumberBetween(PositiveNumber, From, To))
				cout << "Wrong number, please enter a number from " << From << " to " << To << "." << endl;

		} while (!IsNumberBetween(PositiveNumber, From, To));

		return PositiveNumber;
	}

	static clsDate ReadDate() {
		clsDate Date;

		Date.year = ReadYear();
		Date.month = ReadMonth();
		Date.day = ReadDay(Date);

		return Date;
	}

	static clsPeriod ReadPeriod() {
		clsPeriod Period;

		cout << "Enter start date :\n";
		Period.startDate = ReadDate();

		cout << "\nEnter end date :\n";
		Period.endDate = ReadDate();

		return Period;
	}

private:
	static bool IsNumber(std::istream& cin) {
		return !cin.fail();
	}

	static short ReadYear() {
		return ReadPositiveNumber("Enter a year : ");
	}

	static short ReadMonth() {
		return ReadPositiveNumberBetween(1, 12, "\nEnter a month : ");
	}

	static short ReadDay(clsDate Date) {
		return ReadPositiveNumberBetween(1, clsDate::CountMonthDays(Date), "\nEnter a day : ");
	}

};