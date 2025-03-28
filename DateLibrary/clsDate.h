#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "..\StringLibrary\clsString.h"
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class clsDate
{
	enum enDateCompare {Before = -1, Equal = 0, After = 1};

private:
	short _year = 1970;
	short _month = 1;
	short _day = 1;

public:
	clsDate() {
		*this = LocalDate();
	}

	clsDate(string date) {
		*this = StringToDate(date);
	}

	clsDate(short day, short month, short year) {
		_day = day;
		_month = month;
		_year = year;
	}

	clsDate(short dayCount, short year) {
		*this = IncreaseDateByXDays(clsDate(1, 1, year), dayCount);
	}

	void SetYear(short year) {
		_year = year;
	}

	short GetYear() {
		return _year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short year;

	void SetMonth(short month) {
		_month = month;
	}

	short GetMonth() {
		return _month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short month;

	void SetDay(short day) {
		_day = day;
	}

	short GetDay() {
		return _day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short day;

	static bool IsLeapYear(short Year) {
		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
	}

	bool IsLeapYear() {
		return IsLeapYear(_year);
	}

	static short CountMonthDays(short Year, short Month) {
		short MonthsDay[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : MonthsDay[Month - 1]);
	}

	static short CountMonthDays(clsDate Date) {
		return CountMonthDays(Date._year, Date._month);
	}

	short CountMonthDays() {
		return CountMonthDays(_year, _month);
	}

	static short CountYearDays(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}

	short CountYearDays() {
		return CountYearDays(_year);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return Date._day == CountMonthDays(Date._year, Date._month);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate Date) {
		return Date._month == 12;
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(*this);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date))
			{
				Date._year++;
				Date._month = 1;
				Date._day = 1;
			}
			else
			{
				Date._month++;
				Date._day = 1;
			}
		}
		else
		{
			Date._day++;
		}

		return Date;
	}

	void IncreaseDateByOneDay() {
		*this = IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate Date, int DaysToAdd) {
		for (int i = 1; i <= DaysToAdd; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(int DaysToAdd) {
		*this = IncreaseDateByXDays(*this, DaysToAdd);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date) {
		short MonthDays = CountMonthDays(Date._year, Date._month);

		if (Date._day <= MonthDays - 7)
		{
			Date._day += 7;
		}
		else
		{
			if (IsLastMonthInYear(Date))
			{
				Date._year++;
				Date._month = 1;
				Date._day = (7 - (MonthDays - Date._day));
			}
			else
			{
				Date._month++;
				Date._day = (7 - (MonthDays - Date._day));
			}
		}

		return Date;
	}

	void IncreaseDateByOneWeek() {
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, int WeeksToAdd) {
		for (int i = 1; i <= WeeksToAdd; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeeks(int WeeksToAdd) {
		*this = IncreaseDateByXWeeks(*this, WeeksToAdd);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date) {
		if (IsLastMonthInYear(Date))
		{
			Date._year++;
			Date._month = 1;
		}
		else
		{
			Date._month++;
		}

		short MonthDays = CountMonthDays(Date._year, Date._month);

		if (Date._day > MonthDays)
		{
			Date._day = MonthDays;
		}

		return Date;
	}

	void IncreaseDateByOneMonth() {
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, int MonthsToAdd) {
		for (short i = 1; i <= MonthsToAdd; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(int MonthsToAdd) {
		*this = IncreaseDateByXMonths(*this, MonthsToAdd);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date) {
		Date._year++;
		return Date;
	}

	void IncreaseDateByOneYear() {
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, int YearsToAdd) {
		Date._year += YearsToAdd;
		return Date;
	}

	void IncreaseDateByXYears(int YearsToAdd) {
		*this = IncreaseDateByXYears(*this, YearsToAdd);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date) {
		Date._year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade() {
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date, int DecadesToAdd) {
		Date._year += 10 * DecadesToAdd;
		return Date;
	}

	void IncreaseDateByXDecades(int DecadesToAdd) {
		*this = IncreaseDateByXDecades(*this, DecadesToAdd);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date) {
		Date._year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury() {
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMellennium(clsDate Date) {
		Date._year += 1000;
		return Date;
	}

	void IncreaseDateByOneMellennium() {
		*this = IncreaseDateByOneMellennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date) {
		if (Date._day == 1)
		{
			if (Date._month == 1)
			{
				Date._year--;
				Date._month = 12;
				Date._day = 31;
			}
			else
			{
				Date._month--;
				Date._day = CountMonthDays(Date._year, Date._month);
			}
		}
		else
		{
			Date._day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay() {
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, int Days) {
		for (int i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDays(int Days) {
		*this = DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date) {
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek() {
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, int Weeks) {
		for (int i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(int Weeks) {
		*this = DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date) {
		if (Date._month == 1)
		{
			Date._year--;
			Date._month = 12;
		}
		else
		{
			Date._month--;
		}

		short MonthDays = CountMonthDays(Date._year, Date._month);

		if (Date._day > MonthDays)
		{
			Date._day = MonthDays;
		}

		return Date;
	}

	void DecreaseDateByOneMonth() {
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, int Months) {
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(int Months) {
		*this = DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date) {
		Date._year--;
		return Date;
	}

	void  DecreaseDateByOneYear() {
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, int Years) {
		Date._year -= Years;
		return Date;
	}

	void DecreaseDateByXYears(int Years) {
		*this = DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date) {
		Date._year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade() {
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, int Decodes) {
		Date._year -= 10 * Decodes;
		return Date;
	}

	void  DecreaseDateByXDecades(int Decodes) {
		*this = DecreaseDateByXDecades(*this, Decodes);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date) {
		Date._year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury() {
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMellennium(clsDate Date) {
		Date._year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMellennium() {
		*this = DecreaseDateByOneMellennium(*this);
	}

	static clsDate LocalDate() {
		time_t Time = time(0);
		tm* LocalTime = localtime(&Time);

		clsDate localDate(1, 1, 1970);
		localDate._year = LocalTime->tm_year + 1900;
		localDate._month = LocalTime->tm_mon + 1;
		localDate._day = LocalTime->tm_mday;

		return localDate;
	}

	void UpdateToLocalDate() {
		*this = LocalDate();
	}

	static short GetDayOfWeekOrder(short Year, short Month, short Day) {
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + (12 * a) - 2;

		// Sunday = 0, Monday = 1, ...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short GetDayOfWeekOrder(clsDate Date) {
		return GetDayOfWeekOrder(Date._year, Date._month, Date._day);
	}

	short GetDayOfWeekOrder() {
		return GetDayOfWeekOrder(*this);
	}

	static string GetDayName(short DayIndex) {
		string WeekDays[7]{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return WeekDays[DayIndex];
	}

	string GetDayName() {
		return GetDayName(GetDayOfWeekOrder());
	}

	static string GetShortDayName(short DayIndex) {
		string WeekDays[7]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return WeekDays[DayIndex];
	}

	string GetShortDayName() {
		return GetShortDayName(GetDayOfWeekOrder());
	}

	static string GetShortMonthName(short Month) {
		string MonthsName[12]{ "Jun", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Agu", "Sep", "Oct", "Nov", "Dec" };
		return MonthsName[Month - 1];
	}

	string GetShortMonthName() {
		return GetShortMonthName(_month);
	}

	static string DateToString(clsDate Date, bool WithShortDayName = false) {
		string DayShortName = (WithShortDayName ? (GetShortDayName(GetDayOfWeekOrder(Date)) + " , ") : "");
		return DayShortName + to_string(Date._day) + '/' + to_string(Date._month) + '/' + to_string(Date._year);
	}

	string DateToString(bool WithShortDayName = false) {
		return DateToString(*this, WithShortDayName);
	}

	static bool IsDateBeforeAnotherDate(clsDate Date1, clsDate Date2) {
		if (Date1._year != Date2._year)
			return Date1._year < Date2._year;

		if (Date1._month != Date2._month)
			return Date1._month < Date2._month;

		return Date1._day < Date2._day;
	}

	bool IsDateBeforeAnotherDate(clsDate DateForCompare) {
		return IsDateBeforeAnotherDate(*this, DateForCompare);
	}

	static bool IsDateEqualAnotherDate(clsDate Date1, clsDate Date2) {
		return (Date1._year == Date2._year && Date1._month == Date2._month && Date1._day == Date2._day);
	}

	bool IsDateEqualAnotherDate(clsDate DateForCompare) {
		return IsDateEqualAnotherDate(*this, DateForCompare);
	}

	static bool IsDateAfterAnotherDate(clsDate Date1, clsDate Date2) {
		return (!IsDateBeforeAnotherDate(Date1, Date2) && !IsDateEqualAnotherDate(Date1, Date2));
	}

	void IsDateAfterAnotherDate(clsDate DateForCompare) {
		return IsDateAfterAnotherDate(DateForCompare);
	}

	static short DifferenceBetweenDates(clsDate Date1, clsDate Date2, bool InclodingEndDay = false) {
		short Days = 0;

		if (IsDateBeforeAnotherDate(Date1, Date2))
		{
			while (IsDateBeforeAnotherDate(Date1, Date2))
			{
				Date1 = IncreaseDateByOneDay(Date1);
				Days++;
			}

			return InclodingEndDay ? Days + 1 : Days;
		}
		else
		{
			while (IsDateBeforeAnotherDate(Date2, Date1))
			{
				Date2 = IncreaseDateByOneDay(Date2);
				Days++;
			}

			return InclodingEndDay ? (Days * -1) - 1 : Days * -1;
		}

	}

	short DifferenceBetweenDates(clsDate DateForCompare, bool InclodingEndDay = false) {
		return DifferenceBetweenDates(*this, DateForCompare, InclodingEndDay);
	}

	static short CountOfDaysFromBeginingYear(clsDate Date) {
		short NumberOfDays = 0;

		for (short Month = 1; Month <= Date._month - 1; Month++)
		{
			NumberOfDays += CountMonthDays(Date._year, Month);
		}

		return NumberOfDays += Date._day;
	}

	short CountOfDaysFromBeginingYear() {
		return CountOfDaysFromBeginingYear(*this);
	}

	static bool IsEndOfWeek(clsDate Date) {
		return GetDayOfWeekOrder(Date) == 6;
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {
		short DayOrder = GetDayOfWeekOrder(Date);
		return (DayOrder == 5 || DayOrder == 6);
	}

	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short CountDaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - GetDayOfWeekOrder(Date);
	}

	short CountDaysUntilTheEndOfWeek() {
		return CountDaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date) {
		return CountMonthDays(Date._year, Date._month) - Date._day;
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date) {
		return CountYearDays(Date._year) - CountOfDaysFromBeginingYear(Date);
	}

	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	static short ActualVacationDays(clsDate VacationStart, clsDate VacationEnd) {
		short TotalVacationDays = 0;

		while (IsDateBeforeAnotherDate(VacationStart, VacationEnd))
		{
			if (IsBusinessDay(VacationStart))
			{
				TotalVacationDays++;
			}

			VacationStart = IncreaseDateByOneDay(VacationStart);
		}

		return TotalVacationDays;
	}

	short ActualVacationDays(clsDate VacationEnd) {
		return ActualVacationDays(*this, VacationEnd);
	}

	static short CompareDates(clsDate Date1, clsDate Date2) {
		if (IsDateBeforeAnotherDate(Date1, Date2))
			return enDateCompare::Before;

		if (IsDateEqualAnotherDate(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	short CompareDates(clsDate DateForCompare) {
		return CompareDates(*this, DateForCompare);
	}

	static bool IsValidDate(clsDate Date) {
		return !(Date._month < 1 || Date._month > 12 || Date._day < 1 || Date._day > CountMonthDays(Date));
	}

	bool IsValidDate() {
		return IsValidDate(*this);
	}

	static clsDate StringToDate(string DateInString) {
		vector<string> vDate = clsString::Split(DateInString, "/");

		clsDate Date;
		Date._day = stoi(vDate[0]);
		Date._month = stoi(vDate[1]);
		Date._year = stoi(vDate[2]);

		return Date;
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy") {
		DateFormat = clsString::Replace(DateFormat, "dd", to_string(Date._day));
		DateFormat = clsString::Replace(DateFormat, "mm", to_string(Date._month));
		DateFormat = clsString::Replace(DateFormat, "yyyy", to_string(Date._year));

		return DateFormat;
	}

	string FormatDate(string DateFormat = "dd/mm/yyyy") {
		return FormatDate(*this, DateFormat);
	}

	static clsDate GetLargestDate(clsDate FirstDate, clsDate SecondDate) {
		return (CompareDates(FirstDate, SecondDate) == 1 ? FirstDate : SecondDate);
	}

	static clsDate GetSmallestDate(clsDate FirstDate, clsDate SecondDate) {
		return (CompareDates(FirstDate, SecondDate) == -1 ? SecondDate : FirstDate);
	}

	static short CountOfDaysInDate(clsDate BirthdayDate) {
		time_t Time = time(0);
		tm* LocalTime = localtime(&Time);

		clsDate LocalDate;
		LocalDate._year = LocalTime->tm_year + 1900;
		LocalDate._month = LocalTime->tm_mon + 1;
		LocalDate._day = LocalTime->tm_mday;

		return DifferenceBetweenDates(BirthdayDate, LocalDate, true);
	}

	short CountOfDaysInDate() {
		return CountOfDaysInDate(*this);
	}

};