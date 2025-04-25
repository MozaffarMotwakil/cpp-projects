#pragma once
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferRegisterScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen {
	enum enTransactions { Deposit = 1, Withdraaw = 2, TotalBalance = 3, Transfer = 4, TransferRegister = 5, MainMenue = 6 };

private:
    static void _PerformTransactionsScreen(enTransactions transactions) {
        if (transactions != enTransactions::MainMenue) {
            system("cls");
        }

        switch (transactions)
        {
        case enTransactions::Deposit:
            _ShowDepositScreen();
            break;
        case enTransactions::Withdraaw:
            _ShowWithdrawScreen();
            break;
        case enTransactions::TotalBalance:
            _ShowTotalBalanceScreen();
            break;
        case enTransactions::Transfer:
            _ShowTransferScreen();
            break;
        case enTransactions::TransferRegister:
            _ShowTransferRegisterScreen();
        case enTransactions::MainMenue:
            // We doing nothin because already we come back to main menue screen
            break;
        }

        if (transactions != enTransactions::MainMenue) {
            _StopScreen();
        }
    }

    static short _ReadTransactionsMenueChoice() {
        return clsInputeValidate::ReadPositiveNumberBetween(1, 6, "\t\t\t\t\tChoose what do you want to do [1 to 6] : ");
    }

    static void _StopScreen() {
        cout << "\nPress any kay to go back to Transaction Menue...";
        system("pause > 0");
    }

    static void _ShowDepositScreen() {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalanceScreen() {
        clsTotalBalancesScreen::ShowTotalBanacesScreen();
    }
    
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }
    
    static void _ShowTransferRegisterScreen() {
        clsTransferRegisterScreen::ShowTransferRegisterScreen();
    }

public:
    static void ShowTransactionsMenueScreen() {
        short choice = 0;

        do
        {
            string tital = "\t     Transactions Screen";
            system("cls");
            clsScreen::DrawScreenHeder(tital);
            cout << setw(40) << "" << "===========================================\n";
            cout << setw(40) << "" << "\t Transactions Menue Screen\n";
            cout << setw(40) << "" << "===========================================\n";
            cout << setw(40) << "" << "[1] Deposit.\n";
            cout << setw(40) << "" << "[2] Withdraw.\n";
            cout << setw(40) << "" << "[3] Total Balance.\n";
            cout << setw(40) << "" << "[4] Transfer.\n";
            cout << setw(40) << "" << "[5] Transfer Register.\n";
            cout << setw(40) << "" << "[6] Main Menue.\n";
            cout << setw(40) << "" << "===========================================\n";

            choice = _ReadTransactionsMenueChoice();
            _PerformTransactionsScreen((enTransactions)choice);

        } while (choice != enTransactions::MainMenue);

    }

};