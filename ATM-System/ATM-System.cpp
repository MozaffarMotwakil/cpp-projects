#include "..\MyLibrary\MyInputLib.h"
#include "..\MyLibrary\MyFileUtilsLib.h"
#include "..\MyLibrary\MyTextUtilsLib.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

enum enWithdrawType { Quick, Normal};

enum enQuickWithdrawOptions { Twenty = 1, Fifty = 2, OneHundred = 3, TwoHundreds = 4, FourHundreds = 5, SixHundreds = 6, EightHundreds = 7, OneThousand = 8, Exit = 9};

enum enMainMenueOptions { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };

struct stClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance = 0;
    bool DeleteMark = false;
};

string ClientsFilePath = "../BankSystem/Clients.txt";

stClient CurrentClient;

void Login();

void MainMenueScreen();

void ShowQuickWithdrawMenueScreen();

void ShowNormalWithdrawScreen();

stClient ConvertClientLineToRecord(string ClientAsLine) {
    vector<string> vClientParts = MyTextUtilsLib::Split(ClientAsLine, "#//#");

    stClient Client;
    Client.AccountNumber = vClientParts[0];
    Client.PinCode = vClientParts[1];
    Client.Name = vClientParts[2];
    Client.Phone = vClientParts[3];
    Client.Balance = stoi(vClientParts[4]);

    return Client;
}

vector<stClient> LoadClientsFromFile(string FilePath) {
    vector<string> vClientsAsLines = MyFileUtilsLib::LoadDataFromFile(ClientsFilePath);
    vector<stClient> vClients;

    for (string& ClientAsLine : vClientsAsLines) {
        vClients.push_back(ConvertClientLineToRecord(ClientAsLine));
    }

    return vClients;
}

string ConvertClientToLine(const stClient& Client, string Seperator = "#//#") {
    string ClientInLine = "";

    ClientInLine += Client.AccountNumber + Seperator;
    ClientInLine += Client.PinCode + Seperator;
    ClientInLine += Client.Name + Seperator;
    ClientInLine += Client.Phone + Seperator;
    ClientInLine += to_string(Client.Balance);

    return ClientInLine;
}

void SaveClientToFile(string FilePath,const stClient& Client) {
    fstream File;

    File.open(FilePath, ios::out | ios::app);

    if (File.is_open())
    {
        File << ConvertClientToLine(Client) << endl;
        File.close();
    }

}

void RewriteClientsToFile(string FilePath) {
    vector<stClient> vClients = LoadClientsFromFile(FilePath);
    fstream File;

    File.open(ClientsFilePath, ios::out);

    if (File.is_open())
    {
        for (stClient& Client : vClients) {
            if (Client.AccountNumber == CurrentClient.AccountNumber)
            {
                Client.Balance = CurrentClient.Balance;
            }
            
            SaveClientToFile(ClientsFilePath, Client);
        }

        File.close();
    }
}

void GoBackToLoginScreen() {
    Login();
}

void GoBackToMainMenueScreen() {
    cout << "\nPress any kay to go back to main menue screen...";
    system("pause > 0");
    MainMenueScreen();
}

void PrintScreenHeader(string Message) {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\t" << Message << endl;
    cout << "==================================================\n";

}

void ShowCheckBalanceScreen() {
    PrintScreenHeader("Check Balance Screen");
    cout << "Your balance is : " << CurrentClient.Balance << endl;
}

void DisplayWithdrawFailedMessage() {
    cout << "\nAmount Exceeds the balance, make another choice.";
    cout << "\nPress any kay to continue...";
    system("pause > 0");
}

void PerformTransaction(double Amount) {
    CurrentClient.Balance += Amount;
    cout << "\nDone Seccessfuly, New Balance is : " << CurrentClient.Balance << endl;
}

bool ConfirmTransaction() {
    char Answer = MyInputLib::ReadChar("\nAre you sure you want perform this transactions ? (Y/N) : ");
    return (Answer == 'Y' || Answer == 'y');
}

bool CanWithdraw(double Amount) {
    return Amount <= CurrentClient.Balance;
}

void ValidationWithdrawAmount(double Amount, enWithdrawType WithdrawType = enWithdrawType::Quick) {
    if (CanWithdraw(Amount))
    {
        if (ConfirmTransaction())
        {
            PerformTransaction(Amount * -1);
            RewriteClientsToFile(ClientsFilePath);
        }
    }
    else
    {
        DisplayWithdrawFailedMessage();
        (WithdrawType == enWithdrawType::Quick) ? ShowQuickWithdrawMenueScreen() : ShowNormalWithdrawScreen();
    }
}

double ReadDepositAmount() {
    return MyInputLib::ReadPositiveNumber("\nEnter a positive deposit amount : ");
}

void PerformDepositTransaction() {
    int Amount = ReadDepositAmount();

    if (ConfirmTransaction())
    {
        PerformTransaction(Amount);
        RewriteClientsToFile(ClientsFilePath);
    }
}

void ShowDepositScreen() {
    PrintScreenHeader("Deposit Screen");
    PerformDepositTransaction();
}

bool IsAmountMultipleOfFive(double Amount) {
    return int(Amount) % 5 == 0;
}

double ReadWithdrawAmount() {
    double Amount = 0;

    do
    {
        Amount = MyInputLib::ReadPositiveNumber("\nEnter an amount multiple of 5's : ");

    } while (!IsAmountMultipleOfFive(Amount));

    return Amount;
}

void ShowNormalWithdrawScreen() {
    PrintScreenHeader("Normal Withdraw Screen");
    ValidationWithdrawAmount(ReadWithdrawAmount(), enWithdrawType::Normal);
}

void PerformQuickWithdrawMenue(enQuickWithdrawOptions QuickWithdrawMenueOption) {
    switch (QuickWithdrawMenueOption)
    {
    case enQuickWithdrawOptions::Twenty:
        ValidationWithdrawAmount(20);
        break;
    case enQuickWithdrawOptions::Fifty:
        ValidationWithdrawAmount(50);
        break;
    case enQuickWithdrawOptions::OneHundred:
        ValidationWithdrawAmount(100);
        break;
    case enQuickWithdrawOptions::TwoHundreds:
        ValidationWithdrawAmount(200);
        break;
    case enQuickWithdrawOptions::FourHundreds:
        ValidationWithdrawAmount(400);
        break;
    case enQuickWithdrawOptions::SixHundreds:
        ValidationWithdrawAmount(600);
        break;
    case enQuickWithdrawOptions::EightHundreds:
        ValidationWithdrawAmount(800);
        break;
    case enQuickWithdrawOptions::OneThousand:
        ValidationWithdrawAmount(1000);
        break;
    case enQuickWithdrawOptions::Exit:
        GoBackToMainMenueScreen();
        break;
    }
}

short ReadQuickWithdrawMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 9, "Choose what to withdraw [1 to 8] or exit [9] : ");
}

void ShowQuickWithdrawMenueScreen() {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] 20";
    cout << "\t\t[2] 50\n";
    cout << "\t[3] 100";
    cout << "\t\t[4] 200\n";
    cout << "\t[5] 400";
    cout << "\t\t[6] 600\n";
    cout << "\t[7] 800";
    cout << "\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "==================================================\n";
    cout << "\t\tYour balance is : " << CurrentClient.Balance << endl;
    cout << "==================================================\n";
    PerformQuickWithdrawMenue((enQuickWithdrawOptions)ReadQuickWithdrawMenueChoice());
}

void PerformMainMenue(enMainMenueOptions MainMenueOption) {
    system("cls");

    switch (MainMenueOption)
    {
    case enMainMenueOptions::QuickWithdraw:
        ShowQuickWithdrawMenueScreen();
        GoBackToMainMenueScreen();
        break;
    case enMainMenueOptions::NormalWithdraw:
        ShowNormalWithdrawScreen();
        GoBackToMainMenueScreen();
        break;
    case enMainMenueOptions::Deposit:
        ShowDepositScreen();
        GoBackToMainMenueScreen();
        break;
    case enMainMenueOptions::CheckBalance:
        ShowCheckBalanceScreen();
        GoBackToMainMenueScreen();
        break;
    case enMainMenueOptions::Logout:
        GoBackToLoginScreen();
        break;
    }
}

short ReadMainMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 5, "Choose what do you want to do [1 to 5] : ");
}

void MainMenueScreen() {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "==================================================\n";
    PerformMainMenue((enMainMenueOptions)ReadMainMenueChoice());
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient& CurrentClient) {
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);

    for (stClient& Client : vClients) {
        if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode)
        {
            CurrentClient = Client;
            return true;
        }
    }

    return false;
}

bool LoadClientInfo(string AccountNumber, string PinCode, stClient& CurrentClient) {
    return FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient);
}

string ReadAccountNumber() {
    return MyInputLib::ReadString("Enter Account Number : ", true);
}

string ReadPinCode() {
    return MyInputLib::ReadString("Enter PIN Code : ", true);
}

void Login() {
    bool IsValidLogin = true;

    do
    {
        system("cls");
        PrintScreenHeader("   Login Screen");

        if (!IsValidLogin)
        {
            cout << "Invalid an Account number/PIN code" << endl;
        }

        string AccountNumber = ReadAccountNumber();
        string PIN_Code = ReadPinCode();

        IsValidLogin = LoadClientInfo(AccountNumber, PIN_Code, CurrentClient);

    } while (!IsValidLogin);

    MainMenueScreen();
}

int main()
{
    Login();

    return 0;
}