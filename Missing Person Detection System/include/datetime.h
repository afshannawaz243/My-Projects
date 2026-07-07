#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <ctime>
#include <iostream>
using namespace std;

class DateTime {
private:
    int day, month, year;
    int hour, minute;

public:
    DateTime();
    DateTime(int d, int m, int y, int h = 0, int min = 0);
    DateTime(const DateTime& other);
    DateTime& operator=(const DateTime& other);

    string toString() const;
    string toDateOnly() const;

    bool operator<(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
    friend ostream& operator<<(ostream& os, const DateTime& dt);

    int getDay()   const { return day; }
    int getMonth() const { return month; }
    int getYear()  const { return year; }

    static DateTime now();
};

#endif