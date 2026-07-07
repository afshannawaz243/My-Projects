#include "DateTime.h"
#include <sstream>
#include <iomanip>
using namespace std;

DateTime::DateTime() {
    time_t t = time(nullptr);
    struct tm tm_info;
    localtime_s(&tm_info, &t);        // VS-safe version
    day = tm_info.tm_mday;
    month = tm_info.tm_mon + 1;
    year = tm_info.tm_year + 1900;
    hour = tm_info.tm_hour;
    minute = tm_info.tm_min;
}

DateTime::DateTime(int d, int m, int y, int h, int min)
    : day(d), month(m), year(y), hour(h), minute(min) {
}

DateTime::DateTime(const DateTime& other)
    : day(other.day), month(other.month), year(other.year),
    hour(other.hour), minute(other.minute) {
}

DateTime& DateTime::operator=(const DateTime& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hour = other.hour;
        minute = other.minute;
    }
    return *this;
}

string DateTime::toString() const {
    ostringstream oss;
    oss << setfill('0') << setw(2) << day << "/"
        << setw(2) << month << "/" << year
        << " " << setw(2) << hour << ":"
        << setw(2) << minute;
    return oss.str();
}

string DateTime::toDateOnly() const {
    ostringstream oss;
    oss << setfill('0') << setw(2) << day << "/"
        << setw(2) << month << "/" << year;
    return oss.str();
}

bool DateTime::operator<(const DateTime& other) const {
    if (year != other.year)   return year < other.year;
    if (month != other.month)  return month < other.month;
    if (day != other.day)    return day < other.day;
    if (hour != other.hour)   return hour < other.hour;
    return minute < other.minute;
}

bool DateTime::operator==(const DateTime& other) const {
    return day == other.day && month == other.month &&
        year == other.year && hour == other.hour &&
        minute == other.minute;
}

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.toString();
    return os;
}

DateTime DateTime::now() {
    return DateTime();
}