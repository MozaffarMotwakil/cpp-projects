#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

private:
    enMode _mode;
    string _userName;
    string _password;
    int _permissions;
    bool _markedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";

        UserRecord += User.firstName + Seperator;
        UserRecord += User.lastName + Seperator;
        UserRecord += User.email + Seperator;
        UserRecord += User.phone + Seperator;
        UserRecord += User.userName + Seperator;
        UserRecord += clsUtil::EncryptText(User.password) + Seperator;
        UserRecord += to_string(User.permissions);

        return UserRecord;
    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {
        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) {
                vUsers.push_back(_ConvertLinetoUserObject(Line));
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        if (MyFile.is_open())
        {
            string DataLine;
            for (clsUser U : vUsers)
            {
                //we only write records that are not marked for delete.  
                if (U.MarkedForDeleted() == false)
                {
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.userName == userName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    clsUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password, int permissions) 
        : clsPerson(firstName, lastName, email, phone)
    {
        _mode = mode;
        _userName = userName;
        _password = password;
        _permissions = permissions;
    }

    enum enPermitions { AllPermitions = -1, ShowClientsListPermition = 1, AddClientPermition = 2,
        DeleteClientPermition = 4, UpdateClientPermition = 8, FindClientPermition = 16, TransactionsPermition = 32,
        ManageUsersPermition = 64, LoginRegister = 128, CurrencyExchange = 256 };

    bool IsEmpty()
    {
        return (_mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _markedForDelete;
    }

    string GetUserName()
    {
        return _userName;
    }

    void SetUserName(string UserName)
    {
        _userName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string userName;

    void SetPassword(string Password)
    {
        _password = Password;
    }

    string GetPassword()
    {
        return _password;
    }

    __declspec(property(get = GetPassword, put = SetPassword)) string password;

    void SetPermissions(int Permissions)
    {
        _permissions = Permissions;
    }

    short GetPermissions()
    {
        return _permissions;
    }

    __declspec(property(get = GetPermissions, put = SetPermissions)) short permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.userName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode
        
        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.userName == UserName && User.password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {
        switch (_mode) {
        case enMode::EmptyMode:
            return enSaveResults::svFaildEmptyObject;
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;
        case enMode::AddNewMode:
            if (clsUser::IsUserExist(_userName)) {
                return enSaveResults::svFaildUserExists;
            } else {
                _AddNew();
                _mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
    }

    static bool IsUserExist(string UserName) {
        return (!clsUser::Find(UserName).IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.userName == _userName)
            {
                U._markedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string userName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", userName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool HasPermission(enPermitions permission) {
        return ((this->permissions == enPermitions::AllPermitions) || (permission & this->permissions) == permission);
    }

};