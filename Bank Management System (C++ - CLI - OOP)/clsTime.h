#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class clsTime {
private:
	short _hour;
	short _minute;
	short _second;

public:
	clsTime() {
		time_t Time = time(0);
		tm* localTime = localtime(&Time);

		_hour = localTime->tm_hour;
		_minute = localTime->tm_min;
		_second = localTime->tm_sec;
	}

	void SetHour(short hour) {
		_hour = hour;
	}

	short GetHour() {
		return _hour;
	}

	__declspec(property(get = GetHour, put = SetHour)) short hour;

	void SetMinute(short minute) {
		_minute = minute;
	}

	short GetMinute() {
		return _minute;
	}

	__declspec(property(get = GetMinute, put = SetMinute)) short minute;

	void SetSecond(short second) {
		_second = second;
	}

	short GetSecond() {
		return _second;
	}

	__declspec(property(get = GetSecond, put = SetSecond)) short second;

	string TimeToString() {
		return to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
	}

};