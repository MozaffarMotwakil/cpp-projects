#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>
#include <iomanip>

using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:
    static void _PrintClientInfo(clsBankClient& client) {
        cout << "| " << setw(12) << client.firstName;
        cout << "| " << setw(12) << client.lastName;
        cout << "| " << setw(20) << client.GetFullName();
        cout << "| " << setw(20) << client.email;
        cout << "| " << setw(12) << client.phone;
        cout << "| " << setw(15) << client.accountNumber;
        cout << "| " << setw(10) << client.pinCode;
        cout << "| " << setw(10) << client.accountBalance;
        cout << endl;
    }

public:
    static void ShowClientsListScreen() {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string tital = "\t\tClients List Screen";
        string subTital = "\t\t(" + to_string(vClients.size()) + ") Clinet(s)";

        cout << left;
        clsScreen::DrawScreenHeder(tital, subTital);
        cout << "\t\t\t\t\t\tClients List [" << vClients.size() << "] Client(s)";
        cout << "\n________________________________________________________________________________________________________________________________\n\n";
        cout << "| " << setw(12) << "First Name";
        cout << "| " << setw(12) << "Last Name";
        cout << "| " << setw(20) << "Full Name";
        cout << "| " << setw(20) << "Email";
        cout << "| " << setw(12) << "Phone";
        cout << "| " << setw(15) << "Account Number";
        cout << "| " << setw(10) << "Pin Code";
        cout << "| " << setw(10) << "Balance";
        cout << "\n________________________________________________________________________________________________________________________________\n\n";

        if (vClients.size() == 0) {
            cout << "\t\t\t\t\t\tNo Clients Avaliable";
        }
        else {
            for (clsBankClient& client : vClients) {
                _PrintClientInfo(client);
            }
        }

        cout << "\n________________________________________________________________________________________________________________________________\n\n";
    }

};