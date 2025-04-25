#pragma once
#include "clsDate.h"
#include "clsTime.h"
#include "Global.h"
#include <fstream>

class clsLoginHistory {
private:
    struct _stLoginRecord {
        clsDate localDate;
        clsTime localTime;
        string userName;
        string password;
        string permissions;
    };

    static _stLoginRecord _PrepareLoginRecord() {
        _stLoginRecord loginRecord;

        loginRecord.localDate = clsDate();
        loginRecord.localTime = clsTime();
        loginRecord.userName = currentUser.userName;
        loginRecord.password = currentUser.password;
        loginRecord.permissions = to_string(currentUser.permissions);

        return loginRecord;
    }

    static string _ConvertLoginRecordToDataLine(_stLoginRecord loginRecord, string seperator = "#//#") {
        string dateLine;

        dateLine += loginRecord.localDate.DateToString() + " - " + loginRecord.localTime.TimeToString() + seperator;
        dateLine += loginRecord.userName + seperator;
        dateLine += clsUtil::EncryptText(loginRecord.password) + seperator;
        dateLine += loginRecord.permissions;

        return dateLine;
    }

public:
    static void SaveLoginRecord() {
        fstream file;

        file.open("LoginHistory.txt", ios::out | ios::app);

        if (file.is_open())
        {
            _stLoginRecord loginRecord = _PrepareLoginRecord();
            file << _ConvertLoginRecordToDataLine(loginRecord) << endl;
            file.close();
        }
    }

};