#pragma once

#include <iostream>

namespace MyValidationLib {

	bool IsPositiveNumber(int Number) {
		return Number >= 0;
	}

	bool IsNegativeNumber(int Number) {
		return Number < 0;
	}

	bool IsNumberInRange(int Number, int From, int To) {
		return (Number >= From && Number <= To);
	}

	bool IsNumber(std::istream& cin) {
		return !cin.fail();
	}

}