#pragma once
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsTime.h"
#include "Global.h"
#include <fstream>

class clsTransferHistory {
private:
    struct _stTransferRecord {
        clsDate localDate;
        clsTime localTime;
        string sourceAccountNumber;
        string destinationAccountNumber;
        float transferAmount;
        float sourceClientBalance;
        float destinationClientBalance;
        string excutedBy;
    };

    static _stTransferRecord _PrepareTransferRecord(clsBankClient& sourceClient, clsBankClient& destinationClient, float transferAmount) {
        _stTransferRecord transferRecord;

        transferRecord.localDate = clsDate();
        transferRecord.localTime = clsTime();
        transferRecord.sourceAccountNumber = sourceClient.accountNumber;
        transferRecord.destinationAccountNumber = destinationClient.accountNumber;
        transferRecord.transferAmount = transferAmount;
        transferRecord.sourceClientBalance = sourceClient.accountBalance;
        transferRecord.destinationClientBalance = destinationClient.accountBalance;
        transferRecord.excutedBy = currentUser.userName;

        return transferRecord;
    }

    static string _ConvertTransferRecordToDataLine(_stTransferRecord& transferRecord, string seperator = "#//#") {
        string dateLine;

        dateLine += transferRecord.localDate.DateToString() + " - " + transferRecord.localTime.TimeToString() + seperator;
        dateLine += transferRecord.sourceAccountNumber + seperator;
        dateLine += transferRecord.destinationAccountNumber + seperator;
        dateLine += to_string(transferRecord.transferAmount) + seperator;
        dateLine += to_string(transferRecord.sourceClientBalance) + seperator;
        dateLine += to_string(transferRecord.destinationClientBalance) + seperator;
        dateLine += transferRecord.excutedBy;

        return dateLine;
    }

public:
    static void SaveTransferRecord(clsBankClient& sourceClient, clsBankClient& destinationClient, float transferAmount) {
        fstream file;

        file.open("TransferHistory.txt", ios::out | ios::app);

        if (file.is_open())
        {
            _stTransferRecord transferRecord = _PrepareTransferRecord(sourceClient, destinationClient, transferAmount);
            file << _ConvertTransferRecordToDataLine(transferRecord) << endl;
            file.close();
        }
    }

};