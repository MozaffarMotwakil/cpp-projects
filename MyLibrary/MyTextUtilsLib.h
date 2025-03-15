#pragma once

using namespace std;

namespace MyTextUtilsLib {

	string LowerAllString(string Text) {

		for (short i = 0; i < Text.length(); i++)
		{
			Text[i] = tolower(Text[i]);
		}

		return Text;
	}

	string UppperAllString(string Text) {

		for (short i = 0; i < Text.length(); i++)
		{
			Text[i] = toupper(Text[i]);
		}

		return Text;
	}

	char InvertLetterCase(char Character) {
		return islower(Character) ? toupper(Character) : tolower(Character);
	}


	string InvertAllLettersCase(string Text) {
		for (unsigned short i = 0; i < Text.length(); i++)
		{
			Text[i] = InvertLetterCase(Text[i]);
		}

		return Text;
	}


	vector<string> Split(string Text, string Dilimeter) {
		vector<string> vTextParts;
		string Part = "";
		short Position = 0;

		while ((Position = Text.find(Dilimeter)) != string::npos)
		{
			Part = Text.substr(0, Position);

			if (Part != "")
			{
				vTextParts.push_back(Part);
			}

			Text.erase(0, Position + Dilimeter.length());
		}

		if (Part != "")
		{
			vTextParts.push_back(Text);
		}

		return vTextParts;
	}


}