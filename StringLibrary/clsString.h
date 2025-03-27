#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsString
{
private:
	string _value;

public:
	void SetValue(string value) {
		_value = value;
	}

	string GetValue() {
		return _value;
	}

	clsString() {
		_value = "";
	}

	clsString(string value) {
		_value = value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string value;

	static short Length(string value) {
		return value.length();
	}

	short Length() {
		return _value.length();
	}

	static string FirstLetterForEachWordToUpperCase(string Sentence) {
		bool IsFirstLetter = true;

		for (short i = 0; i < Sentence.length(); i++)
		{
			if (Sentence[i] != ' ' && IsFirstLetter)
			{
				Sentence[i] = toupper(Sentence[i]);
			}

			IsFirstLetter = (Sentence[i] == ' ') ? true : false;
		}

		return Sentence;
	}

	void FirstLetterForEachWordToUpperCase() {
		_value = FirstLetterForEachWordToUpperCase(_value);
	}

	static string FirstLetterForEachWordToLowerCase(string Sentence) {
		bool IsFirstLetter = true;

		for (short i = 0; i < Sentence.length(); i++)
		{
			if (Sentence[i] != ' ' && IsFirstLetter)
			{
				Sentence[i] = tolower(Sentence[i]);
			}

			IsFirstLetter = (Sentence[i] == ' ') ? true : false;
		}

		return Sentence;
	}

	void FirstLetterForEachWordToLowerCase() {
		_value = FirstLetterForEachWordToLowerCase(_value);
	}

	static string LettersToLower(string Sentence) {

		for (short i = 0; i < Sentence.length(); i++)
		{
			Sentence[i] = tolower(Sentence[i]);
		}

		return Sentence;
	}

	void LettersToLower() {
		_value = LettersToLower(_value);
	}

	static string LettersToUppers(string Sentence) {

		for (short i = 0; i < Sentence.length(); i++)
		{
			Sentence[i] = toupper(Sentence[i]);
		}

		return Sentence;
	}

	void LettersToUppers() {
		_value = LettersToUppers(_value);
	}

	static char InvertLetterCase(char Character) {
		return islower(Character) ? toupper(Character) : tolower(Character);
	}

	static string InvertLettersCase(string Text) {
		for (unsigned short i = 0; i < Text.length(); i++)
		{
			Text[i] = InvertLetterCase(Text[i]);
		}

		return Text;
	}

	void InvertLettersCase() {
		_value = InvertLettersCase(_value);
	}

	static short CountSmallLetters(string Text) {
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (islower(Text[i]))
			{
				Counter++;
			}
		}

		return Counter;
	}

	short CountSmallLetters() {
		return CountSmallLetters(_value);
	}

	static short CountCapitalLetters(string Text) {
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (isupper(Text[i]))
			{
				Counter++;
			}
		}

		return Counter;
	}

	short CountCapitalLetters() {
		return CountCapitalLetters(_value);
	}

	static short CountSpecificLetter(string Text, char Letter, bool MatchCase = true) {
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (MatchCase)
			{
				if (Text[i] == Letter)
				{
					Counter++;
				}
			}
			else
			{
				if (toupper(Text[i]) == toupper(Letter))
				{
					Counter++;
				}
			}
		}

		return Counter;
	}

	short CountSpecificLetter(char Letter, bool MatchCase = true) {
		return CountSpecificLetter(_value, Letter, MatchCase);
	}

	static bool IsVowel(char Letter) {
		Letter = toupper(Letter);
		return ((Letter == 'A') || (Letter == 'E') || (Letter == 'I') || (Letter == 'O') || (Letter == 'U'));
	}

	static short CountVowels(string Text) {
		short Counter = 0;

		for (char& Letter : Text) {
			if (IsVowel(Letter))
			{
				Counter++;
			}
		}

		return Counter;
	}

	short CountVowels() {
		return CountVowels(_value);
	}

	static short CountWords(string Text) {
		string Dilimeter = " ", Word = "";
		short Counter = 0, Position = 0;

		while ((Position = Text.find(Dilimeter)) != string::npos)
		{
			Word = Text.substr(0, Position);

			if (Word != "")
			{
				Counter++;
			}

			Text.erase(0, Position + Dilimeter.length());
		}

		if (Word != "")
		{
			Counter++;
		}

		return Counter;
	}

	short CountWords() {
		return CountWords(_value);
	}

	static vector<string> Split(string Text, string Dilimeter) {
		string Word = "";
		vector<string> vWords;
		int Position = 0;

		while ((Position = Text.find(Dilimeter)) != string::npos)
		{
			Word = Text.substr(0, Position);

			if (Word != "")
			{
				vWords.push_back(Word);
			}

			Text.erase(0, Position + Dilimeter.length());
		}

		if (Word != "")
		{
			vWords.push_back(Text);
		}

		return vWords;
	}

	vector<string> Split(string Dilimeter) {
		return Split(_value, Dilimeter);
	}

	static string Join(vector<string> vWords, string Dilimeter) {
		string Text = "";

		for (short i = 0; i < vWords.size(); i++)
		{
			Text += vWords.at(i) + Dilimeter;
		}

		return Text.substr(0, Text.length() - Dilimeter.length());
	}

	static string Join(string vWords[], short ArrLength, string Dilimeter) {
		string Text = "";

		for (short i = 0; i < ArrLength; i++)
		{
			Text += vWords[i] + Dilimeter;
		}

		return Text.substr(0, Text.length() - Dilimeter.length());
	}

	static string TrimLeft(string Text) {
		for (short i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ')
				return Text.substr(i, Text.length());
		}

		return Text;
	}

	void TrimLeft() {
		_value = TrimLeft(_value);
	}

	static string TrimRight(string Text) {
		for (short i = Text.length() - 1; i >= 0; i--)
		{
			if (Text[i] != ' ')
				return Text.substr(0, i + 1);
		}

		return Text;
	}

	void TrimRight() {
		_value = TrimRight(_value);
	}

	static string Trim(string Text) {
		return TrimLeft(TrimRight(Text));
	}

	void Trim() {
		_value = Trim(_value);
	}

	static string Reverse(string Text) {
		vector<string> vWords = Split(Text, " ");
		string ReverseText = "";

		for (short i = vWords.size() - 1; i >= 0; i--)
		{
			ReverseText += vWords[i] + " ";
		}

		return ReverseText.substr(0, ReverseText.length() - 1);
	}

	void Reverse() {
		_value = Reverse(_value);
	}

	static string Replace(string Text, string OrginalPart, string NewPart) {
		int OrginalPartPosition = 0;

		while ((OrginalPartPosition = Text.find(OrginalPart)) != string::npos)
		{
			Text.replace(OrginalPartPosition, OrginalPart.length(), NewPart);
		}

		return Text;
	}

	void Replace(string OrginalPart, string NewPart) {
		_value = Replace(_value, OrginalPart, NewPart);
	}

	static string RemovePunctuations(string Text) {
		for (short i = 0; i < Text.length(); i++)
		{
			if (ispunct(Text[i]))
			{
				Text[i] = '\0';
			}
		}

		return Text;
	}

	void RemovePunctuations() {
		_value = RemovePunctuations(_value);
	}

};