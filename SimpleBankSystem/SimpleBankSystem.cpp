#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include "..\..\MyLibrary\MyInputLib.h"

string ClientsFilePath = "Clients.txt";

enum enMainMenueOptions { ShowClientsList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, Exit = 7 };

enum enTransactions { Deposit = 1, Withdraaw = 2, TotalBalance = 3, MainMenue = 4 };

struct stClient {
    string AccountNumber;
    string PIN;
    string Name;
    string Phone;
    int Balance = 0;
    bool DeleteMark = false;
};

using namespace std;

void MainMenueScreen();

void SaveClientToFile(string FilePath, stClient& Client);

void RewriteClientsToFile(vector<stClient>& vClients);

bool IsClientExists(vector<stClient>& vClients, string AccountNumber);

bool IsClientExists(vector<stClient>& vClients, string AccountNumber, stClient& Client);

void GoBackToMainMenue();

void DisplayClientDetails(stClient& Client);

void TransactionsMenueScrean();

void PrintHeader(string Message) {
    cout << "-----------------------------------------\n";
    cout << "\t" << Message;
    cout << "\n-----------------------------------------\n";
}

vector<string> Split(string Text, string Dilimeter = "#//#") {
    vector<string> vTextParts;
    string Part = "";
    short Position = 0;

    while ((Position = Text.find(Dilimeter)) != string::npos)
    {
        Part = Text.substr(0, Position);

        if (Part != "")
        {
            vTextParts.push_back(Part);
        }

        Text.erase(0, Position + Dilimeter.length());
    }

    if (Part != "")
    {
        vTextParts.push_back(Text);
    }

    return vTextParts;
}

string ConvertClientToLine(stClient& Client, string Seperator = "#//#") {
    string ClientInLine = "";

    ClientInLine += Client.AccountNumber + Seperator;
    ClientInLine += Client.PIN + Seperator;
    ClientInLine += Client.Name + Seperator;
    ClientInLine += Client.Phone + Seperator;
    ClientInLine += to_string(Client.Balance);

    return ClientInLine;
}

stClient ConvertLineToClient(string ClientInLine) {
    stClient Client;
    vector<string> vLineParts = Split(ClientInLine);

    Client.AccountNumber = vLineParts[0];
    Client.PIN = vLineParts[1];
    Client.Name = vLineParts[2];
    Client.Phone = vLineParts[3];
    Client.Balance = stoi(vLineParts[4]);

    return Client;
}

vector<string> LoadDataFromFile(string FilePath) {
    vector<string> vLines;
    fstream File;

    File.open(FilePath, ios::in);

    if (File.is_open())
    {
        string Line = "";

        while (getline(File, Line))
        {
            vLines.push_back(Line);
        }

        File.close();
    }

    return vLines;
}

vector<stClient> LoadClientsFromFile(string FilePath) {
    vector<stClient> vClients;
    vector<string> vLiens = LoadDataFromFile(FilePath);

    for (string& Lien : vLiens) {
        vClients.push_back(ConvertLineToClient(Lien));
    }

    return vClients;
}

void ShowExitScrean() {
    PrintHeader("End of Program");
}

int GetTotalBalance() {
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    int TotalBalance = 0;

    for (stClient& Client : vClients) {
        TotalBalance += Client.Balance;
    }

    return TotalBalance;
}

void PrintBriefClintsInfo(vector<stClient>& vClients) {
    for (stClient& Client : vClients) {
        cout << "|" << setw(16) << Client.AccountNumber;
        cout << "|" << setw(30) << Client.Name;
        cout << "|" << setw(12) << to_string(Client.Balance);
        cout << endl;
    }
}

void ShowTotalBalanceScrean() {
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);

    cout << left;
    cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";
    cout << "|" << setw(16) << " Account Number";
    cout << "|" << setw(30) << " Client Name";
    cout << "|" << setw(12) << " Balance";
    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";

    PrintBriefClintsInfo(vClients);

    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";

    cout << "\t\t\t\tTotal Balance = " << GetTotalBalance() << endl;
}

string ValidationAccountNumber(vector<stClient>& vClients) {
    string AccountNumber = MyInputLib::ReadString("\nEnter Account Number : ", true);

    while (!IsClientExists(vClients, AccountNumber))
    {
        AccountNumber = MyInputLib::ReadString("Client with [" + AccountNumber + "] does not exists, Enter Another Account Number : ");
    }

    return AccountNumber;
}

int ValidationWithdrawAmount(stClient& Client) {
    int WithdrawAmount = MyInputLib::ReadPositiveNumber("\nEnter withdraw amount : ");

    while (WithdrawAmount > Client.Balance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Balance;
        WithdrawAmount = MyInputLib::ReadPositiveNumber("\nEnter withdraw amount : ");
    }

    return WithdrawAmount;
}

void WithdrawTransactiom(vector<stClient>& vClients, string AccountNumber) {
    for (stClient& Client : vClients) {
        if (Client.AccountNumber == AccountNumber)
        {
            DisplayClientDetails(Client);

            int WithdrawAmount = ValidationWithdrawAmount(Client);

            char Answer = MyInputLib::ReadChar("\n\nAre you sure you want perform this transactions ? (Y/N) : ");

            if (Answer == 'Y' || Answer == 'y')
            {
                Client.Balance -= WithdrawAmount;
                cout << "\nDone Seccessfuly, New Balance is : " << Client.Balance << endl;
            }

            RewriteClientsToFile(vClients);
            return;
        }
    }
}

void ShowWithdrawScrean() {
    PrintHeader("Withdraw Screan");
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = ValidationAccountNumber(vClients);

    WithdrawTransactiom(vClients, AccountNumber);
}

void GoBackToTransactionsMenue() {
    cout << "\nPress any kay to go back to Transaction Menue...";
    system("pause > 0");
    TransactionsMenueScrean();
}

void DepositTransactiom(vector<stClient>& vClients, string AccountNumber) {
    for (stClient& Client : vClients) {
        if (Client.AccountNumber == AccountNumber)
        {
            DisplayClientDetails(Client);

            short DepositAmount = MyInputLib::ReadPositiveNumber("\nEnter deposit amount : ");

            char Answer = MyInputLib::ReadChar("\nAre you sure you want perform this transactions ? (Y/N) : ");

            if (Answer == 'Y' || Answer == 'y')
            {
                Client.Balance += DepositAmount;
                cout << "\nDone Seccessfuly, New Balance is : " << Client.Balance << endl;
            }

            RewriteClientsToFile(vClients);
            return;
        }
    }
}

void ShowDepositScrean() {
    PrintHeader("Deposit Screan");
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = ValidationAccountNumber(vClients);

    DepositTransactiom(vClients, AccountNumber);
}

void PerformTransactionsScrean(enTransactions Transactions) {
    switch (Transactions)
    {
    case enTransactions::Deposit:
        system("cls");
        ShowDepositScrean();
        GoBackToTransactionsMenue();
        break;
    case enTransactions::Withdraaw:
        system("cls");
        ShowWithdrawScrean();
        GoBackToTransactionsMenue();
        break;
    case enTransactions::TotalBalance:
        system("cls");
        ShowTotalBalanceScrean();
        GoBackToTransactionsMenue();
        break;
    case enTransactions::MainMenue:
        GoBackToMainMenue();
        break;
    }
}

short ReadTransactionsMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 4, "Choose what do you want to do [1 to 4] : ");
}

void TransactionsMenueScrean() {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tTransactions Menue Screan\n";
    cout << "==================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "==================================================\n";
    PerformTransactionsScrean((enTransactions)ReadTransactionsMenueChoice());
}

void DisplayClientDetails(stClient& Client) {
    cout << "\nThe following are the client details :\n";
    cout << "-----------------------------------------\n";
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "PIN Code        : " << Client.PIN << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.Balance << endl;
    cout << "-----------------------------------------\n";
}

void ShowFindClientScrean() {
    PrintHeader("Find Clients Screan");

    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = MyInputLib::ReadString("Enter Account Number : ", true);
    stClient Client;

    if (IsClientExists(vClients, AccountNumber, Client))
    {
        DisplayClientDetails(Client);
    }
    else
    {
        cout << "\nClient with Account Numbe [" + AccountNumber + "] is Not Found!\n";
    }
}

stClient UpdateClientInfo(stClient& Client) {
    Client.PIN = MyInputLib::ReadString("\nEnter PIN Code : ", true);
    Client.Name = MyInputLib::ReadString("Enter Name : ");
    Client.Phone = MyInputLib::ReadString("Enter Phone : ");
    Client.Balance = MyInputLib::ReadPositiveNumber("Enter Balance : ");

    return Client;
}

void ShowUpdateClientScrean() {
    PrintHeader("Update Clients Screan");

    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = MyInputLib::ReadString("Enter Account Number : ", true);
    stClient Client;

    if (IsClientExists(vClients, AccountNumber, Client))
    {
        DisplayClientDetails(Client);
        char UserAswer = MyInputLib::ReadChar("\nAre you sure you want update this client ? (Y/N) : ");

        if (UserAswer == 'Y' || UserAswer == 'y')
        {
            for (stClient& ClientFromVector : vClients) {
                if (ClientFromVector.AccountNumber == AccountNumber)
                {
                    ClientFromVector = UpdateClientInfo(Client);
                    RewriteClientsToFile(vClients);
                    cout << "\n\n-Client Update Successfuly\n";
                    return;
                }
            }
        }

    }
    else
    {
        cout << "\nClient with Account Numbe [" + AccountNumber + "] is Not Found!\n";
    }
}

void RewriteClientsToFile(vector<stClient>& vClients) {
    fstream File;

    File.open(ClientsFilePath, ios::out);

    if (File.is_open())
    {
        for (stClient& Client : vClients) {
            if (Client.DeleteMark != true)
            {
                SaveClientToFile(ClientsFilePath, Client);
            }
        }
    }

    File.close();
    vClients = LoadClientsFromFile(ClientsFilePath); // Update client vector data to delete the client that was don't writing in file
}

bool IsClientExists(vector<stClient>& vClients, string AccountNumber, stClient& Client) {
    for (stClient& CurrentClient : vClients) {
        if (CurrentClient.AccountNumber == AccountNumber)
        {
            Client = CurrentClient;
            return true;
        }
    }

    return false;
}

void SetDeleteMarkForClient(vector<stClient>& vClients, string AccountNumber) {
    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            Client.DeleteMark = true;
            return;
        }
    }
}

void DeleteClientByAccountNumber(vector<stClient>& vClients, string AccountNumber) {
    stClient Client;

    if (IsClientExists(vClients, AccountNumber, Client))
    {
        DisplayClientDetails(Client);
        char DeleteAnswer = MyInputLib::ReadChar("\nAre you sure you want delete this client ? (Y/N) : ");

        if (DeleteAnswer == 'Y' || DeleteAnswer == 'y')
        {
            SetDeleteMarkForClient(vClients, AccountNumber);
            RewriteClientsToFile(vClients);
            cout << "\n-Client Delete Successfuly\n";
        }
    }
    else
    {
        cout << "\nClient with Account Numbe [" + AccountNumber + "] is Not Found!\n";
    }

}

void ShowDeleteClientScrean() {
    PrintHeader("Delete Clients Screan");
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = MyInputLib::ReadString("Enter Account Number : ", true);
    DeleteClientByAccountNumber(vClients, AccountNumber);
}

void SaveClientToFile(string FilePath, stClient& Client) {
    fstream File;

    File.open(FilePath, ios::out | ios::app);

    if (File.is_open())
    {
        File << ConvertClientToLine(Client) << endl;
        File.close();
    }

}

bool IsClientExists(vector<stClient>& vClients, string AccountNumber) {
    for (stClient& CurrentClient : vClients) {
        if (CurrentClient.AccountNumber == AccountNumber)
        {
            return true;
        }
    }

    return false;
}

stClient ReadClient() {
    stClient Client;
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);

    Client.AccountNumber = MyInputLib::ReadString("Enter Account number : ", true);

    while (IsClientExists(vClients, Client.AccountNumber))
    {
        Client.AccountNumber = MyInputLib::ReadString("Client with [" + Client.AccountNumber + "] already exists, Enter Another Account Number : ");
    }

    Client.PIN = MyInputLib::ReadString("Enter PIN Code : ");
    Client.Name = MyInputLib::ReadString("Enter Name : ");
    Client.Phone = MyInputLib::ReadString("Enter Phone : ");
    Client.Balance = MyInputLib::ReadPositiveNumber("Enter Balance : ");

    return Client;
}

void AddNewClient(vector<stClient>& vClients) {
    stClient Client;

    Client = ReadClient();
    vClients.push_back(Client);
    SaveClientToFile(ClientsFilePath, Client);
}

void AddNewClients() {
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    char AddAgain = 'Y';

    do
    {
        cout << "\nAdding New Client :\n\n";
        AddNewClient(vClients);
        AddAgain = MyInputLib::ReadChar("\nClient added seccessfuly, do you want to add more clients ? (Y/N) : ");

    } while (AddAgain == 'Y' || AddAgain == 'y');
}

void ShowAddNewClientsScrean() {
    PrintHeader("Add New Clients Screan");
    AddNewClients();
}

void PrintClintsInfo(vector<stClient>& vClients) {
    for (stClient& Client : vClients) {
        cout << "|" << setw(16) << Client.AccountNumber;
        cout << "|" << setw(12) << Client.PIN;
        cout << "|" << setw(30) << Client.Name;
        cout << "|" << setw(15) << Client.Phone;
        cout << "|" << setw(12) << to_string(Client.Balance);
        cout << endl;
    }
}

void ShowAllClientsScrean() {
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);

    cout << left;
    cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";
    cout << "|" << setw(16) << " Account Number";
    cout << "|" << setw(12) << " PIN Code";
    cout << "|" << setw(30) << " Client Name";
    cout << "|" << setw(15) << " Phone";
    cout << "|" << setw(12) << " Balance";
    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";

    PrintClintsInfo(vClients);

    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";
}

void GoBackToMainMenue() {
    cout << "\nPress any kay to go back to Main Menue...";
    system("pause > 0");
    MainMenueScreen();
}

void PerformMainMenue(enMainMenueOptions Operation) {

    switch (Operation)
    {
    case enMainMenueOptions::ShowClientsList:
        system("cls");
        ShowAllClientsScrean();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::AddClient:
        system("cls");
        ShowAddNewClientsScrean();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::DeleteClient:
        system("cls");
        ShowDeleteClientScrean();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::UpdateClient:
        system("cls");
        ShowUpdateClientScrean();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::FindClient:
        system("cls");
        ShowFindClientScrean();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Transactions:
        system("cls");
        TransactionsMenueScrean();
        break;
    case enMainMenueOptions::Exit:
        system("cls");
        ShowExitScrean();
        break;
    }
}

short ReadMainMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 7, "Choose what do you want to do [1 to 7] : ");
}

void MainMenueScreen() {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tMain Menue Screan\n";
    cout << "==================================================\n";
    cout << "\t[1] Show Clinet List.\n";
    cout << "\t[2] Add New Clinet.\n";
    cout << "\t[3] Delete Clinet.\n";
    cout << "\t[4] Update Clinet Info.\n";
    cout << "\t[5] Find Clinet.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "==================================================\n";
    PerformMainMenue((enMainMenueOptions)ReadMainMenueChoice());
}

int main()
{
    MainMenueScreen();

    return 0;
}