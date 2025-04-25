#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include <fstream>
#include <iomanip>

class clsLoginRegisterScreen : protected clsScreen {
private:
    static  vector <string> _LoadLoginRecordsFromFile()
    {
        vector <string> vRecords;
        fstream file;

        file.open("LoginHistory.txt", ios::in);

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                vRecords.push_back(line);
            }

            file.close();
        }

        return vRecords;
    }

    static void _PrintRecordInfo(string record) {
        vector<string> vRecordParts = clsString::Split(record, "#//#");

        cout << setw(20) << "" << "| " << setw(30) << vRecordParts[0];
        cout << "| " << setw(15) << vRecordParts[1];
        cout << "| " << setw(15) << clsUtil::DecryptText(vRecordParts[2]);
        cout << "| " << setw(15) << vRecordParts[3];
        cout << endl;
    }

public:
    static void ShowLoginRegisterScreen() {
        clsScreen::DrawScreenHeder("\t    Login Register Screen");
        vector<string> vRecords = _LoadLoginRecordsFromFile();

        cout << left;
        cout << setw(20) << "\n" << "_________________________________________________________________________________\n\n";
        cout << setw(20) << "" << "| " << setw(30) << "Date/Time";
        cout << "| " << setw(15) << "User Nsme";
        cout << "| " << setw(15) << "Password";
        cout << "| " << setw(15) << "Permissions";
        cout << setw(20) << "\n" << "_________________________________________________________________________________\n\n";

        if (vRecords.size() == 0) {
            cout << "\t\t\t\t\t\t\tNo Records Avaliable in System";
        }
        else {
            for (string record : vRecords) {
                _PrintRecordInfo(record);
            }
        }

        cout << setw(20) << "\n" << "_________________________________________________________________________________\n\n";
    }

};