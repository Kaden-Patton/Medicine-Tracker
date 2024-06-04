#include "Date.h"

std::string Date::getDay() const {
    return this->day;
}

std::string Date::getMonth() const {
    return this->month;
}

std::string Date::getYear() const {
    return this->year;
}

std::string Date::toString() const {
    return this->day + "/" + this->month + "/" + this->year;
}

bool Date::isNumeric(const std::string& str) const {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool Date::isValid(const std::string& day, const std::string& month, const std::string& year) const {
    // Check if day, month, and year contain only numeric characters
    if (!isNumeric(day) && !isNumeric(month) && !isNumeric(year)) {
        return false;
    }

    // Convert day, month, and year to integers
    int dayValue = std::stoi(day);
    int monthValue = std::stoi(month);
    int yearValue = std::stoi(year);

    // Check if day is within the valid range (1-31)
    if (dayValue < 1 || dayValue > 31) {
        return false;
    }

    // Check if month is within the valid range (1-12)
    if (monthValue < 1 || monthValue > 12) {
        return false;
    }

    // Check if year is within the valid range (0-2024)
    if (yearValue < 0 || yearValue > 2024) {
        return false;
    }

    return true;
}
