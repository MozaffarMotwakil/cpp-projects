#pragma once

using namespace std;

namespace MyDateUtilsLib {

    short ConvertDateToWeakDayNumber(short Year, short Month, short Day) {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        // Sunday = 0, Monday = 1, ...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    string GetDayName(short Day) {
        string WeekDays[7]{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        return WeekDays[Day];
    }

}