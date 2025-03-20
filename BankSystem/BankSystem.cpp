#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include "..\..\..\MyLibrary\MyInputLib.h"

string ClientsFilePath = "Clients.txt";
string UsersFilePath = "Users.txt";

enum enPermitions { ShowUserListPermition = 1, AddUserPermition = 2, DeleteUserPermition = 4, UpdateUserPermition = 8, FindUserPermition = 16, TransactionsPermition = 32, ManageUsersPermition = 64 };

enum enManageUsersOptions { ShowUsersList = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, GoToMainMenue = 6};

enum enMainMenueOptions { ShowClientsList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, Loguot = 8 };

enum enTransactions { Deposit = 1, Withdraaw = 2, TotalBalance = 3, MainMenue = 4 };

struct stClient {
    string AccountNumber;
    string PIN;
    string Name;
    string Phone;
    int Balance = 0;
    bool DeleteMark = false;
};

struct stUser {
    string UserName;
    string Password;
    short Permissions;
    bool DeleteMark = false;
};

using namespace std;

void Login();

void MainMenueScreen(stUser User);

void TransactionsMenueScreen(stUser User);

void ManageUsersMenueScreen(stUser User);

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

void SaveClientToFile(string FilePath, stClient& Client) {
    fstream File;

    File.open(FilePath, ios::out | ios::app);

    if (File.is_open())
    {
        File << ConvertClientToLine(Client) << endl;
        File.close();
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

stUser ConvertLineToUser(string UserInLineFromFile) {
    vector<string> vUserParts = Split(UserInLineFromFile);
    stUser User;

    User.UserName = vUserParts[0];
    User.Password = vUserParts[1];
    User.Permissions = stoi(vUserParts[2]);

    return User;
}

string ConvertUserToLine(stUser& User, string Seperator = "#//#") {
    string UserInLine = "";

    UserInLine += User.UserName + Seperator;
    UserInLine += User.Password + Seperator;
    UserInLine += to_string(User.Permissions);

    return UserInLine;
}

vector<stUser> LoadUsersFromFile(string FilePath) {
    vector<string> vUsersInLinesFromFile = LoadDataFromFile(UsersFilePath);
    vector<stUser> vUsers;

    for (string& UserInLine : vUsersInLinesFromFile) {
        vUsers.push_back(ConvertLineToUser(UserInLine));
    }
    
    return vUsers;
}

void SaveUserToFile(string FilePath, stUser& User) {
    fstream File;

    File.open(UsersFilePath, ios::out | ios::app);

    if (File.is_open())
    {
        File << ConvertUserToLine(User) << endl;
        File.close();
    }

}

void RewriteUsersToFile(vector<stUser>& vUsers) {
    fstream File;

    File.open(UsersFilePath, ios::out);

    if (File.is_open())
    {
        for (stUser& User : vUsers) {
            if (User.DeleteMark != true)
            {
                SaveUserToFile(UsersFilePath, User);
            }
        }
    }

    File.close();
    vUsers = LoadUsersFromFile(ClientsFilePath); // Update users vector data to delete the user that was don't writing in file
}

string ReadUserName() {
    return MyInputLib::ReadString("Enter Username : ", true);
}

string ReadPassword() {
    return MyInputLib::ReadString("Enter Password : ", true);
}

short ReadPermitions() {
    short Permissions = 0;

    char Answer = MyInputLib::ReadChar("Do you want to give this user full access ? (Y/N) : ");

    if (Answer == 'Y' || Answer == 'y')
    {
        Permissions = -1;
    }
    else
    {
        cout << "\nDo you want to give access to :\n";

        Answer = MyInputLib::ReadChar("\nShow client list ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::ShowUserListPermition : 0);

        Answer = MyInputLib::ReadChar("\nAdd new client ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::AddUserPermition : 0);

        Answer = MyInputLib::ReadChar("\nDelete client ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::DeleteUserPermition : 0);

        Answer = MyInputLib::ReadChar("\nUpdate client ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::UpdateUserPermition : 0);

        Answer = MyInputLib::ReadChar("\nFind client ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::FindUserPermition : 0);

        Answer = MyInputLib::ReadChar("\nTransactions ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::TransactionsPermition : 0);

        Answer = MyInputLib::ReadChar("\nManage users ? (Y/N) : ");
        Permissions += (Answer == 'Y' || Answer == 'y' ? enPermitions::ManageUsersPermition : 0);
    }

    return Permissions;
}

void GoBackToLoginScreen() {
    Login();
}

void GoBackToMainMenue(stUser User) {
    cout << "\nPress any kay to go back to Main Menue...";
    system("pause > 0");
    MainMenueScreen(User);
}

void DisplayUserDetails(stUser& User) {
    cout << "\nThe following are the user details :\n";
    cout << "-----------------------------------------\n";
    cout << "User Name  : " << User.UserName << endl;
    cout << "Password   : " << User.Password << endl;
    cout << "Permitions : " << User.Permissions << endl;
    cout << "-----------------------------------------\n";
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

bool IsClientExists(vector<stClient>& vClients, string AccountNumber) {
    for (stClient& CurrentClient : vClients) {
        if (CurrentClient.AccountNumber == AccountNumber)
        {
            return true;
        }
    }

    return false;
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

bool IsUserExistsByUserName(string UserName) {
    vector<stUser> vUsers = LoadUsersFromFile(UsersFilePath);

    for (stUser& User : vUsers) {
        if (User.UserName == UserName)
        {
            return true;
        }
    }

    return false;
}

bool IsUserExistsByUserName(string UserName, stUser& UserToDisplayInfo) {
    vector<stUser> vUsers = LoadUsersFromFile(UsersFilePath);

    for (stUser& User : vUsers) {
        if (User.UserName == UserName)
        {
            UserToDisplayInfo = User;
            return true;
        }
    }

    return false;
}

void ShowFindUserScreen() {
    PrintHeader("Find Users Screen");

    vector<stUser> vUsers = LoadUsersFromFile(ClientsFilePath);
    string UserName = ReadUserName();
    stUser User;

    if (IsUserExistsByUserName(UserName, User))
    {
        DisplayUserDetails(User);
    }
    else
    {
        cout << "\nUser with Username [" + UserName + "] is Not Found!\n";
    }
}

stUser UpdateUserInfo(stUser& User) {
    User.Password = ReadPassword();
    User.Permissions = ReadPermitions();

    return User;
}

void ShowUpdateUserScreen() {
    PrintHeader("Update Users Screen");

    vector<stUser> vUsers = LoadUsersFromFile(ClientsFilePath);
    string UserName = MyInputLib::ReadString("Enter Username : ", true);
    stUser User;

    if (IsUserExistsByUserName(UserName, User))
    {
        DisplayUserDetails(User);
        char UserAswer = MyInputLib::ReadChar("\nAre you sure you want update this client ? (Y/N) : ");

        if (UserAswer == 'Y' || UserAswer == 'y')
        {
            for (stUser& User : vUsers) {
                if (User.UserName == UserName)
                {
                    UpdateUserInfo(User);
                    RewriteUsersToFile(vUsers);
                    cout << "\n\n-User Update Successfuly\n";
                    return;
                }
            }
        }

    }
    else
    {
        cout << "\nUser with Username [" + UserName + "] is Not Found!\n";
    }
}

void SetDeleteMarkToUser(vector<stUser>& vUsers, string UserName) {
    for (stUser& User : vUsers)
    {
        if (User.UserName == UserName)
        {
            User.DeleteMark = true;
            return;
        }
    }
}

void DeleteUserByUserName(vector<stUser>& vUsers, string UserName) {
    stUser User;

    if (IsUserExistsByUserName(UserName, User))
    {
        DisplayUserDetails(User);
        char DeleteAnswer = MyInputLib::ReadChar("\nAre you sure you want delete this user ? (Y/N) : ");

        if (DeleteAnswer == 'Y' || DeleteAnswer == 'y')
        {
            SetDeleteMarkToUser(vUsers, UserName);
            RewriteUsersToFile(vUsers);
            cout << "\n-User Delete Successfuly\n";
        }
    }
    else
    {
        cout << "\nUser with Username [" << UserName << "] is Not Found!\n";
    }

}

void ShowDeleteUserScreen() {
    PrintHeader("Delete Users Screan");
    vector<stUser> vUsers = LoadUsersFromFile(UsersFilePath);
    string AccountNumber = MyInputLib::ReadString("Enter Username : ", true);
    DeleteUserByUserName(vUsers, AccountNumber);
}

stUser ReadUser() {
    stUser User;

    User.UserName = ReadUserName();

    while (IsUserExistsByUserName(User.UserName))
    {
        cout << "\nUser with [" << User.UserName << "] already exists, please enter another username : ";
        getline(cin, User.UserName);
    }

    User.Password = ReadPassword();
    User.Permissions = ReadPermitions();

    return User;
}

void AddNewUser() {
   stUser User = ReadUser();
   SaveUserToFile(UsersFilePath, User);
}

void AddNewUsers() {
    char AddAgain = 'N';

    do
    {
        cout << "Adding new user :\n\n";
        AddNewUser();
        AddAgain = MyInputLib::ReadChar("\nClient added seccessfuly, Are you want to add more users ? (Y/N) : ");

    } while (AddAgain == 'Y' || AddAgain == 'y');
}

void ShowAddNewUsersScreen() {
    PrintHeader("\tAdd New User Screan");
    AddNewUsers();
}

void PrintUsersInfo(vector<stUser>& vUsers) {
    for (stUser& User : vUsers) {
        cout << "|" << setw(30) << User.UserName;
        cout << "|" << setw(15) << User.Password;
        cout << "|" << setw(15) << User.Permissions;
        cout << endl;
    }
}

void ShowAllUsersScreen() {
    vector<stUser> vUsers = LoadUsersFromFile(UsersFilePath);

    cout << left;
    cout << "\t\t\t\tUsers List (" << vUsers.size() << ") Client(s).";
    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";
    cout << "|" << setw(30) << " User Name";
    cout << "|" << setw(15) << " Password";
    cout << "|" << setw(15) << " Permisstions";
    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";

    PrintUsersInfo(vUsers);

    cout << "\n________________________________________________";
    cout << "_______________________________________\n\n";
}

void GoBackToManageUsersMenue(stUser User) {
    cout << "\nPress any kay to go back to Manage Users Menue...";
    system("pause > 0");
    ManageUsersMenueScreen(User);
}

void PerformManageUsersMenue(enManageUsersOptions ManageUsersOption, stUser User) {
    switch (ManageUsersOption)
    {
    case enManageUsersOptions::ShowUsersList:
        system("cls");
        ShowAllUsersScreen();
        GoBackToManageUsersMenue(User);
        break;
    case enManageUsersOptions::AddUser:
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToManageUsersMenue(User);
        break;
    case enManageUsersOptions::DeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue(User);
        break;
    case enManageUsersOptions::UpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenue(User);
        break;
    case enManageUsersOptions::FindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue(User);
        break;
    case enManageUsersOptions::GoToMainMenue:
        GoBackToMainMenue(User);
        break;
    }
}

short ReadManageUsersMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 6, "Choose what do you want to do [1 to 6] : ");
}

void ManageUsersMenueScreen(stUser User) {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tManage Users Screan\n";
    cout << "==================================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "==================================================\n";
    PerformManageUsersMenue((enManageUsersOptions)ReadManageUsersMenueChoice(), User);
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

void ShowWithdrawScreen() {
    PrintHeader("Withdraw Screan");
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = ValidationAccountNumber(vClients);

    WithdrawTransactiom(vClients, AccountNumber);
}

void GoBackToTransactionsMenue(stUser User) {
    cout << "\nPress any kay to go back to Transaction Menue...";
    system("pause > 0");
    TransactionsMenueScreen(User);
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

void PerformTransactionsScreen(enTransactions Transactions, stUser User) {
    switch (Transactions)
    {
    case enTransactions::Deposit:
        system("cls");
        ShowDepositScrean();
        GoBackToTransactionsMenue(User);
        break;
    case enTransactions::Withdraaw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenue(User);
        break;
    case enTransactions::TotalBalance:
        system("cls");
        ShowTotalBalanceScrean();
        GoBackToTransactionsMenue(User);
        break;
    case enTransactions::MainMenue:
        GoBackToMainMenue(User);
        break;
    }
}

short ReadTransactionsMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 4, "Choose what do you want to do [1 to 4] : ");
}

void TransactionsMenueScreen(stUser User) {
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tTransactions Menue Screan\n";
    cout << "==================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "==================================================\n";
    PerformTransactionsScreen((enTransactions)ReadTransactionsMenueChoice(), User);
}

void ShowFindClientScreen() {
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

void SetDeleteMarkToClient(vector<stClient>& vClients, string AccountNumber) {
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
            SetDeleteMarkToClient(vClients, AccountNumber);
            RewriteClientsToFile(vClients);
            cout << "\n-Client Delete Successfuly\n";
        }
    }
    else
    {
        cout << "\nClient with Account Numbe [" + AccountNumber + "] is Not Found!\n";
    }

}

void ShowDeleteClientScreen() {
    PrintHeader("Delete Clients Screan");
    vector<stClient> vClients = LoadClientsFromFile(ClientsFilePath);
    string AccountNumber = MyInputLib::ReadString("Enter Account Number : ", true);
    DeleteClientByAccountNumber(vClients, AccountNumber);
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
        cout << "Adding New Client :\n\n";
        AddNewClient(vClients);
        AddAgain = MyInputLib::ReadChar("\nClient added seccessfuly, do you want to add more clients ? (Y/N) : ");

    } while (AddAgain == 'Y' || AddAgain == 'y');
}

void ShowAddNewClientsScreen() {
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

void ShowAllClientsScreen() {
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

void ShowAccessDeniedScreen() {
    cout << "-----------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You don't have permition to do this,\n";
    cout << "Please contact your admin.\n";
    cout << "-----------------------------------------\n";
}

void PerformMainMenue(enMainMenueOptions Operation, stUser User) {

    switch (Operation)
    {
    case enMainMenueOptions::ShowClientsList:
        system("cls");
        (User.Permissions == -1 || enPermitions::ShowUserListPermition & User.Permissions) ? ShowAllClientsScreen() : ShowAccessDeniedScreen();
        GoBackToMainMenue(User);
        break;
    case enMainMenueOptions::AddClient:
        system("cls");
        (User.Permissions == -1 || enPermitions::AddUserPermition & User.Permissions) ? ShowAddNewClientsScreen() : ShowAccessDeniedScreen();
        GoBackToMainMenue(User);
        break;
    case enMainMenueOptions::DeleteClient:
        system("cls");
        (User.Permissions == -1 || enPermitions::DeleteUserPermition & User.Permissions) ? ShowDeleteClientScreen() : ShowAccessDeniedScreen();
        GoBackToMainMenue(User);
        break;
    case enMainMenueOptions::UpdateClient:
        system("cls");
        (User.Permissions == -1 || enPermitions::UpdateUserPermition & User.Permissions) ? ShowUpdateClientScrean() : ShowAccessDeniedScreen();
        GoBackToMainMenue(User);
        break;
    case enMainMenueOptions::FindClient:
        system("cls");
        (User.Permissions == -1 || enPermitions::FindUserPermition & User.Permissions) ? ShowFindClientScreen() : ShowAccessDeniedScreen();
        GoBackToMainMenue(User);
        break;
    case enMainMenueOptions::Transactions:
        system("cls");
        if (User.Permissions == -1 || enPermitions::TransactionsPermition & User.Permissions)
        {
            TransactionsMenueScreen(User);
        }
        else
        {
            ShowAccessDeniedScreen();
            GoBackToMainMenue(User);
        }
        break;
    case enMainMenueOptions::ManageUsers:
        system("cls");
        if (User.Permissions == -1 || enPermitions::ManageUsersPermition & User.Permissions)
        {
            ManageUsersMenueScreen(User);
        }
        else
        {
            ShowAccessDeniedScreen();
            GoBackToMainMenue(User);
        }
        break;
    case enMainMenueOptions::Loguot:
        system("cls");
        GoBackToLoginScreen();
        break;
    }
}

short ReadMainMenueChoice() {
    return MyInputLib::ReadPositiveNumberInRange(1, 8, "Choose what do you want to do [1 to 7] : ");
}

void MainMenueScreen(stUser User) {
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
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "==================================================\n";
    PerformMainMenue((enMainMenueOptions)ReadMainMenueChoice(), User);
}

bool IsUserExistsByUserNameAndPassword(string UserName, string Password, stUser& CurrentUser) {
    vector<stUser> vUsers = LoadUsersFromFile(UsersFilePath);

    for (stUser& User : vUsers) {
        if (User.UserName == UserName && User.Password == Password)
        {
            CurrentUser = User;
            return true;
        }
    }

    return false;
}

stUser ReadCurrentUser() {
    stUser User;

    string UserName = ReadUserName();
    string Password = ReadPassword();

    while (!IsUserExistsByUserNameAndPassword(UserName, Password, User))
    {
        system("cls");
        PrintHeader("\tLogin Screen");
        cout << "Invalid Username/Password" << endl;
        UserName = ReadUserName();
        Password = ReadPassword();
    }

    return User;
}

void Login() {
    PrintHeader("\tLogin Screen");
    stUser CurrentUser = ReadCurrentUser();
    MainMenueScreen(CurrentUser);
}

int main()
{
    Login();

    return 0;
}