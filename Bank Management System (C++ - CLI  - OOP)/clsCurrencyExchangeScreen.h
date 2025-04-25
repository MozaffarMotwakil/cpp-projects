#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculaterScreen.h"
class clsCurrencyExchangeScreen :protected clsScreen {
private:
    enum enCurrencyExchangeOptions { ListCurrencies = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculater = 4, MainMenue = 5 };

    static void _PerformCurrencyExchangeScreen(enCurrencyExchangeOptions option) {
        if (option != enCurrencyExchangeOptions::MainMenue) {
            system("cls");
        }

        switch (option)
        {
        case enCurrencyExchangeOptions::ListCurrencies:
            _ShowCurrenciesListScreen();
            break;
        case enCurrencyExchangeOptions::FindCurrency:
            _ShowFindCurrencyScreen();
            break;
        case enCurrencyExchangeOptions::UpdateRate:
            _ShowUpdateRateScreen();
            break;
        case enCurrencyExchangeOptions::CurrencyCalculater:
            _ShowCurrencyCalculaterScreen();
            break;
        case enCurrencyExchangeOptions::MainMenue:
            // We doing nothin because already we come back to main menue screen
            break;
        }

        if (option != enCurrencyExchangeOptions::MainMenue) {
            _StopScreen();
        }
    }

    static short _ReadCurrencyExchangeMenueChoice() {
        return clsInputeValidate::ReadPositiveNumberBetween(1, 5, "\t\t\t\t\tChoose what do you want to do [1 to 5] : ");
    }

    static void _StopScreen() {
        cout << "\nPress any kay to go back to Transaction Menue...";
        system("pause > 0");
    }

    static void _ShowCurrenciesListScreen() {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }
    
    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen() {
        clsUpdateRateScreen::ShowUpdateRateScreen();
    }

     static void _ShowCurrencyCalculaterScreen() {
         clsCurrencyCalculaterScreen::ShowCurrencyCalculaterScreen();
     }

public:
    static void ShowCurrencyExchangeScreen() {
        short choice = 0;

        do
        {
            system("cls");
            clsScreen::DrawScreenHeder("\tCurrency Exchange Screen");
            cout << setw(40) << "" << "===========================================\n";
            cout << setw(40) << "" << "\t Currency Exchange Menue\n";
            cout << setw(40) << "" << "===========================================\n";
            cout << setw(40) << "" << "[1] List Currencies.\n";
            cout << setw(40) << "" << "[2] Find Currency.\n";
            cout << setw(40) << "" << "[3] Update Rate.\n";
            cout << setw(40) << "" << "[4] Currency Calculater.\n";
            cout << setw(40) << "" << "[5] Main Menue.\n";
            cout << setw(40) << "" << "===========================================\n";

            choice = _ReadCurrencyExchangeMenueChoice();
            _PerformCurrencyExchangeScreen((enCurrencyExchangeOptions)choice);

        } while (choice != enCurrencyExchangeOptions::MainMenue);

    }
};

