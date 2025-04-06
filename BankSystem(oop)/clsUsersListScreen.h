#pragma once
#include "clsUser.h"
#include "clsScreen.h"
#include <iomanip>

class clsUsersListScreen : protected clsScreen {
private:
    static void _PrintUserInfo(clsUser& user) {
        cout << "| " << setw(12) << user.firstName;
        cout << "| " << setw(12) << user.lastName;
        cout << "| " << setw(20) << user.GetFullName();
        cout << "| " << setw(20) << user.email;
        cout << "| " << setw(12) << user.phone;
        cout << "| " << setw(15) << user.userName;
        cout << "| " << setw(10) << user.password;
        cout << "| " << setw(12) << user.permissions;
        cout << endl;
    }

public:
    static void ShowUsersListScreen() {
        vector<clsUser> vUsers = clsUser::GetUsersList();
        string tital = "\t\tUsers List Screen";
        string subTital = "\t\t(" + to_string(vUsers.size()) + ") User(s)";

        cout << left;
        clsScreen::DrawScreenHeder(tital, subTital);
        cout << "\t\t\t\t\t\tUsers List [" << vUsers.size() << "] User(s)";
        cout << "\n________________________________________________________________________________________________________________________________\n\n";
        cout << "| " << setw(12) << "First Name";
        cout << "| " << setw(12) << "Last Name";
        cout << "| " << setw(20) << "Full Name";
        cout << "| " << setw(20) << "Email";
        cout << "| " << setw(12) << "Phone";
        cout << "| " << setw(15) << "User Name";
        cout << "| " << setw(10) << "Password";
        cout << "| " << setw(12) << "Permissions";
        cout << "\n________________________________________________________________________________________________________________________________\n\n";

        if (vUsers.size() == 0) {
            cout << "\t\t\t\t\t\tNo Users Avaliable";
        }
        else {
            for (clsUser& user : vUsers) {
                _PrintUserInfo(user);
            }
        }

        cout << "\n________________________________________________________________________________________________________________________________\n\n";
    }

};