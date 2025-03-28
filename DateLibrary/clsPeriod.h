#pragma once
#include "clsDate.h"
#include "clsDate.h"

class clsPeriod
{
private:
	clsDate _startDate;
	clsDate _endDate;

public:
	clsPeriod() {} 

	clsPeriod(clsDate endDate) : _endDate(endDate) {}

	clsPeriod(clsDate startDate, clsDate endDate) : _startDate(startDate), _endDate(endDate) {}

	void SetStartDate(clsDate startDate) {
		_startDate = startDate;
	}

	clsDate GetStartDate() {
		return _startDate;
	}

	__declspec(property(get = GetStartDate, put = SetStartDate)) clsDate startDate;

	void SetEndDate(clsDate endDate) {
		_endDate = endDate;
	}

	clsDate GetEndDate() {
		return _endDate;
	}

	__declspec(property(get = GetEndDate, put = SetEndDate)) clsDate endDate;

	void Print() {
		cout << "Start date: " << _startDate.DateToString() << ", End date: " << _endDate.DateToString() << endl;
	}

		static bool IsOverlapPeriods(clsPeriod FirstPeriod, clsPeriod SecondPeriod) {
		return !(clsDate::CompareDates(SecondPeriod.endDate, FirstPeriod.startDate) == -1 || clsDate::CompareDates(SecondPeriod.startDate, FirstPeriod.endDate) == 1);
	}

	static short PeriodLength(clsPeriod Period, bool IncludeEndDay = false) {
		return clsDate::DifferenceBetweenDates(Period.startDate, Period.endDate, IncludeEndDay);
	}

	static bool IsDateWithinPeriod(clsDate Date, clsPeriod Period) {
		return !(clsDate::CompareDates(Date, Period.startDate) == -1 || clsDate::CompareDates(Date, Period.endDate) == 1);
	}

	static short CountOverlapDays(clsPeriod FirstPeriod, clsPeriod SecondPeriod) {
		if (IsOverlapPeriods(FirstPeriod, SecondPeriod))
		{
			clsPeriod NewPeriod;
			NewPeriod.startDate = clsDate::GetLargestDate(FirstPeriod.startDate, SecondPeriod.startDate);
			NewPeriod.endDate = clsDate::GetSmallestDate(FirstPeriod.endDate, SecondPeriod.endDate);
			return PeriodLength(NewPeriod);
		}

		return 0;
	}

};