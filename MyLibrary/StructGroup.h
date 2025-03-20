#pragma once

struct stDate {
	int unsigned Year;
	short unsigned Month;
	short unsigned Day;
};

struct stPeriod {
	stDate StartDate;
	stDate EndDate;
};
