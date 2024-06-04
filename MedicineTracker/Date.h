#pragma once
#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class Date {

public:
    Date() {
        this->day = "01";
        this->month = "01";
        this->year = "2000";
    }

    Date(const std::string& day) : Date() {
        if (!isValid(day, month, year)) {
            throw std::invalid_argument("Invalid date input");
        }
        this->day = day;
    }

    Date(const std::string& day, const std::string& month) : Date(day) {
        if (!isValid(day, month, year)) {
            throw std::invalid_argument("Invalid date input");
        }
        this->month = month;
    }

    Date(const std::string& day, const std::string& month, const std::string& year) : Date(day, month) {
        if (!isValid(day, month, year)) {
            throw std::invalid_argument("Invalid date input");
        }
        this->year = year;
    }

    friend inline std::ostream& operator<<( std::ostream& stream, const Date& date) {
        return stream << date.toString();
    }
    
    std::string getDay() const;
    std::string getMonth() const;
    std::string getYear() const;

private:
    std::string day, month, year;
    std::string toString() const;
    bool isNumeric(const std::string&) const;
    bool isValid(const std::string&, const std::string&, const std::string&) const;

};