#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include <iomanip>
#include "clsAddNewUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"

class clsManageUsersScreen :
    public clsScreen
{
    enum enManageUsersOptions { ShowUsersList = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, GoToMainMenue = 6 };

private:
    static void _PerformManageUsersMenue(enManageUsersOptions ManageUsersOption) {
        switch (ManageUsersOption)
        {
        case enManageUsersOptions::ShowUsersList:
            system("cls");
            _ShowAllUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersOptions::AddUser:
            system("cls");
            _ShowAddNewUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersOptions::DeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersOptions::UpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersOptions::FindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case enManageUsersOptions::GoToMainMenue:
            // We doing nothin because already we come back to main menue screen
            break;
        }
    }

    static short _ReadManageUsersMenueChoice() {
        return clsInputeValidate::ReadPositiveNumberBetween(1, 6, "\t\t\t\t\tChoose what do you want to do [1 to 6] : ");
    }

    static void _GoBackToManageUsersMenue() {
        cout << "\nPress any kay to go back to Manage Users Menue...";
        system("pause > 0");
        ManageUsersMenueScreen();
    }

    static void _ShowAllUsersScreen() {
        clsUsersListScreen::ShowUsersListScreen();
    }

    static void _ShowAddNewUsersScreen() {
        clsAddNewUsersScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUserScreen();
    }

public:
    static void ManageUsersMenueScreen() {
        system("cls");
        clsScreen::DrawScreenHeder("\t     Manage Users Screen");
        cout << setw(40) << "" << "===========================================\n";
        cout << setw(40) << "" << "\t     Manage Users Menue\n";
        cout << setw(40) << "" << "===========================================\n";
        cout << setw(40) << "" << "[1] List Users.\n";
        cout << setw(40) << "" << "[2] Add New User.\n";
        cout << setw(40) << "" << "[3] Delete User.\n";
        cout << setw(40) << "" << "[4] Update User Info.\n";
        cout << setw(40) << "" << "[5] Find User.\n";
        cout << setw(40) << "" << "[6] Main Menue.\n";
        cout << setw(40) << "" << "===========================================\n";
        _PerformManageUsersMenue((enManageUsersOptions)_ReadManageUsersMenueChoice());
    }

};