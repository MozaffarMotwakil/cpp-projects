#pragma once

#include <vector>
#include <fstream>

using namespace std;

name namespace MyFileUtilsLib {

    vector<string> LoadDataFromFile(string FilePath) {
        vector<string> vLiens;
        fstream File;

        File.open(FilePath, ios::in);

        if (File.is_open())
        {
            string RecordInLine = "";

            while (getline(File, RecordInLine))
            {
                vLiens.push_back(RecordInLine);
            }

            File.close();
        }
    }

}