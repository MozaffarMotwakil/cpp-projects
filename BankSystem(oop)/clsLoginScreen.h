#pragma once
#include "ClsInputValidate.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsLoginHistory.h"

class clsLoginScreen : protected clsScreen {
private:
	static bool _Login() {
        bool isInvalidLogin = false;
        short loginAttemptsLeft = 3;

        do
        {
            string userName = clsInputeValidate::ReadString("\nEnter Username : ", true);
            string password = clsInputeValidate::ReadString("Enter Password : ", true);

            currentUser = clsUser::Find(userName, password);
            isInvalidLogin = currentUser.IsEmpty();

            if (isInvalidLogin) {
                cout << "\nInvalid Username/Password\n";
                cout << "You have " << --loginAttemptsLeft << " Trails to login\n";
                if (loginAttemptsLeft == 0) return false;
            }

        } while (isInvalidLogin);
        
        clsLoginHistory::SaveLoginRecord();
        clsMainScreen::MainMenueScreen();
        return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		clsScreen::DrawScreenHeder("\t\tLogin Screen");
        return _Login();
	}

};