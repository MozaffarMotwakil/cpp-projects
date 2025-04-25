#pragma once
#include "clsScreen.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen {
private:
    static  vector <string> _LoadCurrenciesFromFile()
    {
        vector <string> vCurrencies;
        fstream file;

        file.open("Currencies.txt", ios::in);

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                vCurrencies.push_back(line);
            }

            file.close();
        }

        return vCurrencies;
    }

    static void _PrintCurrencyInfo(string currencyInfo) {
        vector<string> vCurrencyInfoParts = clsString::Split(currencyInfo, "#//#");

        cout << setw(12) << "" << "| " << setw(28) << vCurrencyInfoParts[0];
        cout << "| " << setw(5) << vCurrencyInfoParts[1];
        cout << "| " << setw(40) << vCurrencyInfoParts[2];
        cout << "| " << setw(10) << stof(vCurrencyInfoParts[3]);
        cout << endl;
    }

public:
    static void ShowCurrenciesListScreen() {
        vector<string> vCurrencies = _LoadCurrenciesFromFile();
        string subTital = "\t     (" + to_string(vCurrencies.size()) + ") Currency";
        clsScreen::DrawScreenHeder("\t  Currencies List Screen", subTital);

        cout << left;
        cout << setw(12) << "\n" << "_______________________________________________________________________________________________\n\n";
        cout << setw(12) << "" << "| " << setw(28) << "Country";
        cout << "| " << setw(5) << "Code";
        cout << "| " << setw(40) << "Name";
        cout << "| " << setw(10) << "Rate/(1$)";
        cout << setw(12) << "\n" << "_______________________________________________________________________________________________\n\n";

        if (vCurrencies.size() == 0) {
            cout << "\t\t\t\t\t\t\tNo Records Avaliable in System";
        }
        else {
            for (string transferRecord : vCurrencies) {
                _PrintCurrencyInfo(transferRecord);
            }
        }

        cout << setw(12) << "\n" << "_______________________________________________________________________________________________\n\n";
    }
};