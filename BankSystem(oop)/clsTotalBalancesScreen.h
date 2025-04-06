#pragma once
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsScreen.h"
#include <iostream>
#include <iomanip>

class clsTotalBalancesScreen : protected clsScreen {
private:
    static void _PrintShortClientInfo(clsBankClient& client) {
        cout << setw(35) << "" << "| " << setw(15) << client.accountNumber;
        cout << "| " << setw(20) << client.GetFullName();
        cout << "| " << setw(10) << client.accountBalance;
        cout << endl;
    }

public:
    static void ShowTotalBanacesScreen() {
        clsScreen::DrawScreenHeder("\t    Total Balances Screen");
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        cout << left;
        cout << setw(35) << "\n" << "\t\tClients List [" << vClients.size() << "] Client(s)";
        cout << setw(35) << "\n" << "______________________________________________________\n\n";
        cout << setw(35) << "" << "| " << setw(15) << "Account Number";
        cout << "| " << setw(20) << "Client Name";
        cout << "| " << setw(10) << "Balance";
        cout << setw(35) << "\n" << "______________________________________________________\n\n";

        if (vClients.size() == 0) {
            cout << "\t\t\t\t\t\t\tNo Clients Avaliable in System";
        }
        else {
            for (clsBankClient& client : vClients) {
                _PrintShortClientInfo(client);
            }
        }

        cout << setw(35) << "\n" << "______________________________________________________\n\n";
        float totalBalances = clsBankClient::GetTotalBalances();
        cout << setw(35) << "" << "\t\tTotal Balances = " << totalBalances << endl;
        cout << setw(35) << "" << "(" << clsUtil::NumberToText(totalBalances) << ")" << endl;
    }

};