#pragma once
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "Global.h"
#include <iostream>
#include <iomanip>
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
    enum enMainMenueOptions { ShowClientsList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5,
        Transactions = 6, ManageUsers = 7, LoginRegister = 8, CurrencyExchange = 9, Logout = 10 };

private:
    static void _PerformMainMenue(enMainMenueOptions Operation) {
        system("cls");

        switch (Operation)
        {
        case enMainMenueOptions::ShowClientsList:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::ShowClientsListPermition)) {
                _ShowAllClientsScreen();
            }
            break;
        case enMainMenueOptions::AddClient:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::AddClientPermition)) {
                _ShowAddNewClientsScreen();
            }
            break;
        case enMainMenueOptions::DeleteClient:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::DeleteClientPermition)) {
                _ShowDeleteClientScreen();
            }
            break;
        case enMainMenueOptions::UpdateClient:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::UpdateClientPermition)) {
                _ShowUpdateClientScreen();
            }
            break;
        case enMainMenueOptions::FindClient:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::FindClientPermition)) {
                _ShowFindClientScreen();
            }
            break;
        case enMainMenueOptions::Transactions:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::TransactionsPermition)) {
                _ShowTransactionsMenueScreen();
            }
            break;
        case enMainMenueOptions::ManageUsers:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::ManageUsersPermition)) {
                _ShowManageUsersMenueScreen();
            }
            break;
        case enMainMenueOptions::LoginRegister:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::LoginRegister)) {
                _ShowLoginRegisterScreen();
            }
            break;
        case enMainMenueOptions::CurrencyExchange:
            if (clsScreen::CheckAccessRight(clsUser::enPermitions::CurrencyExchange)) {
                _ShowCurrencyExchangeScreen();
            }
            break;
        case enMainMenueOptions::Logout:
            _Logout();
            break;
        }

        if (Operation != enMainMenueOptions::Logout)
        {
            _StopScreen();
        }
    }

    static short _ReadMainMenueChoice() {
        return clsInputeValidate::ReadPositiveNumberBetween(1, 10, "\t\t\t\t\tChoose what do you want to do [1 to 10] : ");
    }

    static void _StopScreen() {
        cout << "\nPress any kay to go back to Main Menue...";
        system("pause > 0");
    }

    static void _ShowAllClientsScreen() {
        clsClientsListScreen::ShowClientsListScreen();
    }

    static void _ShowAddNewClientsScreen() {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen() {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen() {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    
    static void _ShowFindClientScreen() {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenueScreen() {
        clsTransactionsScreen::ShowTransactionsMenueScreen();
    }

    static void _ShowManageUsersMenueScreen() {
        clsManageUsersScreen::ManageUsersMenueScreen();
    }
    
    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    
    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
    }

    static void _Logout() {
        currentUser = clsUser::Find("", "");
    }

public:
    static void MainMenueScreen() {
        short choice = 0;

        do 
        {
            system("cls");
            clsScreen::DrawScreenHeder("\t\t Main Menue");
            cout << setw(40) << "" << "===========================================\n";
            cout << setw(40) << "" << "\t      Main Menue Screen\n";
            cout << setw(40) << "" << "===========================================\n";
            cout << setw(40) << "" << "[1] Show Clinet List.\n";
            cout << setw(40) << "" << "[2] Add New Clinet.\n";
            cout << setw(40) << "" << "[3] Delete Clinet.\n";
            cout << setw(40) << "" << "[4] Update Clinet Info.\n";
            cout << setw(40) << "" << "[5] Find Clinet.\n";
            cout << setw(40) << "" << "[6] Transactions.\n";
            cout << setw(40) << "" << "[7] Manage Users.\n";
            cout << setw(40) << "" << "[8] Login Register.\n";
            cout << setw(40) << "" << "[9] Currency Exchange.\n";
            cout << setw(40) << "" << "[10] Logout.\n";
            cout << setw(40) << "" << "===========================================\n";

            choice = _ReadMainMenueChoice();
            _PerformMainMenue((enMainMenueOptions)choice);

        } while (choice != enMainMenueOptions::Logout);
    }

};