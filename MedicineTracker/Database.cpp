#include "Database.h"

sqlite3* Database::s_database = nullptr;
std::string Database::s_databasePath = "";
const wchar_t* Database::MUTEX_NAME = L"KP.MED_TRACKER.MUTEX";
HANDLE Database::hMutex = {};

bool Database::Initialize(const std::string& databasePath)
{
    if (!AquireMutexLock()) {
        return false;
    }
    s_databasePath = databasePath;
    int result = sqlite3_open(s_databasePath.c_str(), &s_database);
    if (result != SQLITE_OK)
    {
        return false;
    }

    const char* createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS medicine (
            id INTEGER PRIMARY KEY,
            name TEXT,
            dosage TEXT,
            time_taken TEXT,
            date_taken TEXT,
            notes TEXT
        )
    )";

    char* errorMessage = nullptr;
    result = sqlite3_exec(s_database, createTableQuery, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK)
    {
        if (errorMessage != nullptr)
        {
            sqlite3_free(errorMessage);
        }
        return false;
    }

    return true;
}

void Database::Shutdown()
{
    sqlite3_close(s_database);
    ReleaseMutexLock();
}

bool Database::Insert(const std::string& name, const std::string& dosage, const std::string& timeTaken, const std::string& dateTaken, const std::string& notes)
{
    const char* insertQuery = R"(
        INSERT INTO medicine (name, dosage, time_taken, date_taken, notes)
        VALUES (?, ?, ?, ?, ?)
    )";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(s_database, insertQuery, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        return false;
    }

    // Bind the parameter values to the prepared statement
    sqlite3_bind_text(statement, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, dosage.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, timeTaken.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, dateTaken.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, notes.c_str(), -1, SQLITE_TRANSIENT);

    // Execute the prepared statement
    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return (result == SQLITE_DONE);
}

bool Database::Delete(const int ID) {
    const char* deleteQuery = "DELETE FROM medicine WHERE id = ?";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(s_database, deleteQuery, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(statement, 1, ID);
    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    return (result == SQLITE_DONE);
}

bool Database::GetRecords(std::vector<Record>& records)
{
    const char* selectQuery = "SELECT * FROM medicine";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(s_database, selectQuery, -1, &statement, nullptr);
    if (result != SQLITE_OK)
    {
        return false;
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        Record record;
        record.id = sqlite3_column_int(statement, 0);
        record.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        record.dosage = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
        record.timeTaken = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
        record.dateTaken = reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
        record.notes = reinterpret_cast<const char*>(sqlite3_column_text(statement, 5));

        records.push_back(record);
    }

    sqlite3_finalize(statement);
    return true;
}

bool Database::AquireMutexLock() {
    hMutex = CreateMutex(NULL, TRUE, MUTEX_NAME);
    
    if (hMutex == NULL) {
        return false;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return false;
        CloseHandle(hMutex);
    }

    return true;
}

bool Database::ReleaseMutexLock() {
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return true;
}
