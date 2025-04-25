#pragma once
#include "clsScreen.h"
#include <fstream>
#include <iomanip>

class clsTransferRegisterScreen : protected clsScreen {
private:
    static  vector <string> _LoadTransferRecordsFromFile()
    {
        vector <string> vRecords;
        fstream file;

        file.open("TransferHistory.txt", ios::in);

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

    static void _PrintTransferRecordInfo(string record) {
        vector<string> vRecordParts = clsString::Split(record, "#//#");

        cout << setw(15) << "" << "| " << setw(20) << vRecordParts[0];
        cout << "| " << setw(10) << vRecordParts[1];
        cout << "| " << setw(10) << vRecordParts[2];
        cout << "| " << setw(16) << stof(vRecordParts[3]);
        cout << endl;
    }

public:
    static void ShowTransferRegisterScreen() {
        clsScreen::DrawScreenHeder("\t  Transfer Register Screen");
        vector<string> vRecords = _LoadTransferRecordsFromFile();

        cout << left;
        cout << setw(15) << "\n" << "__________________________________________________________________________________________________\n\n";
        cout << setw(15) << "" << "| " << setw(25) << "Country";
        cout << "| " << setw(5) << "Code";
        cout << "| " << setw(30) << "Name";
        cout << "| " << setw(10) << "Rate/(1$)";
        cout << setw(15) << "\n" << "__________________________________________________________________________________________________\n\n";

        if (vRecords.size() == 0) {
            cout << "\t\t\t\t\t\t\tNo Records Avaliable in System";
        }
        else {
            for (string transferRecord : vRecords) {
                _PrintTransferRecordInfo(transferRecord);
            }
        }

        cout << setw(15) << "\n" << "__________________________________________________________________________________________________\n\n";
    }

};