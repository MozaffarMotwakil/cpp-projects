#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "..\MyLibrary\StructGroup.h"
#include "..\MyLibrary\MyTextUtilsLib.h"
#include <string>
#include <ctime>
#include <vector>

using namespace std;

namespace MyDateUtilsLib {

	enum enDateCompare { After = 1, Equal = 0, Before = -1 };
	
	bool IsLeapYear(short Year) {
		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
	}

	short GetMonthDays(short Year, short Month) {
		short MonthsDay[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : MonthsDay[Month - 1]);
	}

	short GetMonthDays(stDate Date) {
		return GetMonthDays(Date.Year, Date.Month);
	}

	short GetYearDays(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}

	bool IsLastDayInMonth(stDate Date) {
		return Date.Day == GetMonthDays(Date.Year, Date.Month);
	}

	bool IsLastMonthInYear(stDate Date) {
		return Date.Month == 12;
	}

	stDate IncreaseDateByOneDay(stDate Date) {
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date))
			{
				Date.Year++;
				Date.Month = 1;
				Date.Day = 1;
			}
			else
			{
				Date.Month++;
				Date.Day = 1;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	stDate IncreaseDateByXDays(stDate Date, int DaysToAdd) {
		for (int i = 1; i <= DaysToAdd; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneWeek(stDate Date) {
		short MonthDays = GetMonthDays(Date.Year, Date.Month);

		if (Date.Day <= MonthDays - 7)
		{
			Date.Day += 7;
		}
		else
		{
			if (IsLastMonthInYear(Date))
			{
				Date.Year++;
				Date.Month = 1;
				Date.Day = (7 - (MonthDays - Date.Day));
			}
			else
			{
				Date.Month++;
				Date.Day = (7 - (MonthDays - Date.Day));
			}
		}

		return Date;
	}

	stDate IncreaseDateByXWeeks(stDate Date, int WeeksToAdd) {
		for (int i = 1; i <= WeeksToAdd; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneMonth(stDate Date) {
		if (IsLastMonthInYear(Date))
		{
			Date.Year++;
			Date.Month = 1;
		}
		else
		{
			Date.Month++;
		}

		short MonthDays = GetMonthDays(Date.Year, Date.Month);

		if (Date.Day > MonthDays)
		{
			Date.Day = MonthDays;
		}

		return Date;
	}

	stDate IncreaseDateByXMonths(stDate Date, int MonthsToAdd) {
		for (short i = 1; i <= MonthsToAdd; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneYear(stDate Date) {
		Date.Year++;
		return Date;
	}

	stDate IncreaseDateByXYears(stDate Date, int YearsToAdd) {
		for (int i = 1; i <= YearsToAdd; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXYearsFaster(stDate Date, int YearsToAdd) {
		Date.Year += YearsToAdd;
		return Date;
	}

	stDate IncreaseDateByOneDecade(stDate Date) {
		Date.Year += 10;
		return Date;
	}

	stDate IncreaseDateByXDecades(stDate Date, int DecodesToAdd) {
		for (int i = 1; i <= DecodesToAdd; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXDecadesFaster(stDate Date, int DecodesToAdd) {
		Date.Year += 10 * DecodesToAdd;
		return Date;
	}

	stDate IncreaseDateByOneCentury(stDate Date) {
		Date.Year += 100;
		return Date;
	}

	stDate IncreaseDateByOneMellennium(stDate Date) {
		Date.Year += 1000;
		return Date;
	}

	stDate DecreaseDateByOneDay(stDate Date) {
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Year--;
				Date.Month = 12;
				Date.Day = 31;
			}
			else
			{
				Date.Month--;
				Date.Day = GetMonthDays(Date.Year, Date.Month);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	stDate DecreaseDateByXDays(stDate Date, int Days) {
		for (int i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	stDate DecreaseDateByOneWeek(stDate Date) {
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	stDate DecreaseDateByXWeeks(stDate Date, int Weeks) {
		for (int i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	stDate DecreaseDateByOneMonth(stDate Date) {
		if (Date.Month == 1)
		{
			Date.Year--;
			Date.Month = 12;
		}
		else
		{
			Date.Month--;
		}

		short MonthDays = GetMonthDays(Date.Year, Date.Month);

		if (Date.Day > MonthDays)
		{
			Date.Day = MonthDays;
		}

		return Date;
	}

	stDate DecreaseDateByXMonths(stDate Date, int Months) {
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	stDate DecreaseDateByOneYear(stDate Date) {
		Date.Year--;
		return Date;
	}

	stDate DecreaseDateByXYears(stDate Date, int Years) {
		for (int i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	stDate DecreaseDateByXYearsFaster(stDate Date, int Years) {
		Date.Year -= Years;
		return Date;
	}

	stDate DecreaseDateByOneDecade(stDate Date) {
		Date.Year -= 10;
		return Date;
	}

	stDate DecreaseDateByXDecades(stDate Date, int Decodes) {
		for (int i = 1; i <= Decodes; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	stDate DecreaseDateByXDecadesFaster(stDate Date, int Decodes) {
		Date.Year -= 10 * Decodes;
		return Date;
	}

	stDate DecreaseDateByOneCentury(stDate Date) {
		Date.Year -= 100;
		return Date;
	}

	stDate DecreaseDateByOneMellennium(stDate Date) {
		Date.Year -= 1000;
		return Date;
	}

	stDate GetLocalDate() {
		time_t Time = time(0);
		tm* LocalTime = localtime(&Time);

		stDate LocalDate;
		LocalDate.Year = LocalTime->tm_year + 1900;
		LocalDate.Month = LocalTime->tm_mon + 1;
		LocalDate.Day = LocalTime->tm_mday;

		return LocalDate;
	}

    short WeekDayOrder(short Year, short Month, short Day) {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        // Sunday = 0, Monday = 1, ...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

	short WeekDayOrder(stDate Date) {
		return WeekDayOrder(Date.Year, Date.Month, Date.Day);
	}

    string GetDayName(short Day) {
        string WeekDays[7]{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        return WeekDays[Day];
    }

	string GetShortDayName(short DayIndex) {
		string WeekDays[7]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return WeekDays[DayIndex];
	}

	string GetShortMonthName(short Month) {
		string MonthsName[12]{ "Jun", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Agu", "Sep", "Oct", "Nov", "Dec" };
		return MonthsName[Month - 1];
	}

	string DateToString(stDate Date, bool WithShortDayName = false) {
		string DayShortName = (WithShortDayName ? (GetShortDayName(WeekDayOrder(Date)) + " , ") : "");
		return DayShortName + to_string(Date.Day) + '/' + to_string(Date.Month) + '/' + to_string(Date.Year);
	}

	bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
		if (Date1.Year != Date2.Year)
			return Date1.Year < Date2.Year;

		if (Date1.Month != Date2.Month)
			return Date1.Month < Date2.Month;

		return Date1.Day < Date2.Day;
	}

	bool IsDate1EqualDate2(stDate Date1, stDate Date2) {
		return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
	}

	bool IsDate1AfterDate2(stDate Date1, stDate Date2) {
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	short DifferenceDates(stDate Date1, stDate Date2, bool InclodingEndDay = false) {
		short Days = 0;

		if (IsDate1BeforeDate2(Date1, Date2))
		{
			while (IsDate1BeforeDate2(Date1, Date2))
			{
				Date1 = IncreaseDateByOneDay(Date1);
				Days++;
			}

			return InclodingEndDay ? Days + 1 : Days;
		}
		else
		{
			while (IsDate1BeforeDate2(Date2, Date1))
			{
				Date2 = IncreaseDateByOneDay(Date2);
				Days++;
			}

			return InclodingEndDay ? (Days * -1) - 1 : Days * -1;
		}

	}

	short NumberOfDaysFromBeginingYear(stDate Date) {
		short NumberOfDays = 0;

		for (short Month = 1; Month <= Date.Month - 1; Month++)
		{
			NumberOfDays += GetMonthDays(Date.Year, Month);
		}

		return NumberOfDays += Date.Day;
	}

	stDate AddDaysToDate(stDate Date, short DaysToAdd) {
		short RemainingDays = DaysToAdd + NumberOfDaysFromBeginingYear(Date);
		Date.Month = 1;

		while (true)
		{
			short MonthDays = GetMonthDays(Date.Year, Date.Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Year++;
					Date.Month = 1;
				}

			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	bool IsEndOfWeek(stDate Date) {
		return WeekDayOrder(Date) == 6;
	}

	bool IsWeekEnd(stDate Date) {
		short DayOrder = WeekDayOrder(Date);
		return (DayOrder == 5 || DayOrder == 6);
	}

	bool IsBusinessDay(stDate Date) {
		return !IsWeekEnd(Date);
	}

	short DaysUntilTheEndOfWeek(stDate Date) {
		return 6 - WeekDayOrder(Date);
	}

	short DaysUntilTheEndOfMonth(stDate Date) {
		return GetMonthDays(Date.Year, Date.Month) - Date.Day;
	}

	short DaysUntilTheEndOfYear(stDate Date) {
		return GetYearDays(Date.Year) - NumberOfDaysFromBeginingYear(Date);
	}

	short ActualVacationDays(stDate VacationStart, stDate VacationEnd) {
		short TotalVacationDays = 0;

		while (IsDate1BeforeDate2(VacationStart, VacationEnd))
		{
			if (IsBusinessDay(VacationStart))
			{
				TotalVacationDays++;
			}

			VacationStart = IncreaseDateByOneDay(VacationStart);
		}

		return TotalVacationDays;
	}

	short CompareDates(stDate Date1, stDate Date2) {
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	bool IsOverlapPeriods(stPeriod FirstPeriod, stPeriod SecondPeriod) {
		return !(CompareDates(SecondPeriod.EndDate, FirstPeriod.StartDate) == -1 || CompareDates(SecondPeriod.StartDate, FirstPeriod.EndDate) == 1);
	}

	short PeriodLength(stPeriod Period, bool IncludeEndDay = false) {
		return DifferenceDates(Period.StartDate, Period.EndDate, IncludeEndDay);
	}

	bool IsDateWithinPeriod(stDate Date, stPeriod Period) {
		return !(CompareDates(Date, Period.StartDate) == -1 || CompareDates(Date, Period.EndDate) == 1);
	}


	stDate GetLargestDate(stDate FirstDate, stDate SecondDate) {
		return (CompareDates(FirstDate, SecondDate) == 1 ? FirstDate : SecondDate);
	}

	stDate GetSmallestDate(stDate FirstDate, stDate SecondDate) {
		return (CompareDates(FirstDate, SecondDate) == -1 ? SecondDate : FirstDate);
	}

	short CountOverlapDays(stPeriod FirstPeriod, stPeriod SecondPeriod) {
		if (IsOverlapPeriods(FirstPeriod, SecondPeriod))
		{
			stPeriod NewPeriod;
			NewPeriod.StartDate = GetLargestDate(FirstPeriod.StartDate, SecondPeriod.StartDate);
			NewPeriod.EndDate = GetSmallestDate(FirstPeriod.EndDate, SecondPeriod.EndDate);
			return PeriodLength(NewPeriod);
		}

		return 0;
	}

	bool IsValidDate(stDate Date) {
		return !(Date.Month < 1 || Date.Month > 12 || Date.Day < 1 || Date.Day > GetMonthDays(Date));
	}

	stDate StringToDate(string DateInString) {
		vector<string> vDate = MyTextUtilsLib::Split(DateInString, "/");

		stDate Date;
		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;
	}

	string FormatDate(stDate Date, string DateFormat = "dd/mm/yyyy") {
		DateFormat = MyTextUtilsLib::Replce(DateFormat, "dd", to_string(Date.Day));
		DateFormat = MyTextUtilsLib::Replce(DateFormat, "mm", to_string(Date.Month));
		DateFormat = MyTextUtilsLib::Replce(DateFormat, "yyyy", to_string(Date.Year));

		return DateFormat;
	}

}