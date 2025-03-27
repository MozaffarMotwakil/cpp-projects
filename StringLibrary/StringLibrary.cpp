#include <iostream>
#include "clsString.h"

using namespace std;

int main()
{
	clsString str("Hi, i'm mozaffar motwakil");
	cout << "The text: " << str.value << endl;

	cout << "Word count in the text: " << str.CountWords() << endl;

	str.FirstLetterForEachWordToUpperCase();
	cout << "First letter to upper case: " << str.value << endl;

	str.Replace("Mozaffar", "Ahmed");
	cout << "Replacing \"Mozaffar\" to \"Ahmed\": " << str.value << endl;

	return 0;
}