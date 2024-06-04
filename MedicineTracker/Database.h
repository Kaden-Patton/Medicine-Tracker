#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
#include <Windows.h>
#include "Record.h"

class Database
{
public:
    static bool Initialize(const std::string&);
    static void Shutdown();

    static bool Insert(const std::string& name, const std::string& dosage, const std::string& timeTaken, const std::string& dateTaken, const std::string& notes);
    static bool Delete(const int ID);
    static bool GetRecords(std::vector<Record>& records);

private:
    Database() {}

    static sqlite3* s_database;
    static std::string s_databasePath;
    static const wchar_t* MUTEX_NAME;
    static HANDLE hMutex;

    static bool AquireMutexLock();
    static bool ReleaseMutexLock();

};