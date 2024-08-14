#ifndef DATETIME_H_
#define DATETIME_H_

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

// PLANNING REPLACE datetime MANAGER BY A C++-STYLE ADPATHER OF LIBRARY time.h FUNCTIONS

namespace trainsys {

// numbers of days per month
const int mday_number_[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// total numbers of days per month in prefix order
const int prefix_total_[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

/**
 * @brief a date manager
 *
 * records date in a common year, where there's 28 days in Feb and 365 days in total
 * date info is formatted as mm-dd. (for example, August 17th -> 08-17)
 * support several date calculations and type conversions
 *
 */
struct Date {
    int mon;
    int mday;

    Date() = default;
    Date(int mday_, int mon_);
    Date(const Date &o) = default;
    explicit Date(const char * str);
    ~Date() = default;

    Date &operator+=(int days);
    Date &operator-=(int days);
    Date operator+(int days);
    Date operator-(int days);

    operator std::string() const;
    friend std::ostream &operator<<(std::ostream &os, const Date &date);

    friend bool operator==(const Date &lhs, const Date &rhs);
    friend bool operator!=(const Date &lhs, const Date &rhs);
    friend bool operator<(const Date &lhs, const Date &rhs);
    friend bool operator>(const Date &lhs, const Date &rhs);
    friend bool operator<=(const Date &lhs, const Date &rhs);
    friend bool operator>=(const Date &lhs, const Date &rhs);

    friend int operator-(const Date &lhs, const Date &rhs);
};

/**
 * @brief a time manager, with date info attached
 *
 * records a point of time, instead of a duration
 * date info is attached for time changes across the midnight
 * time info is formatted as hh:mm, and uses a 24-hour clock (for example, ten to two in the
 * afternoon -> 13:50) support several time calculations and type conversions when used for display
 * or conversion, date info is omitted
 *
 */
struct Time {
    Date date;
    int min;
    int hour;

    Time() = default;
    Time(int min_, int hour_, int mday_ = 1, int mon_ = 1, int year_ = 1);
    Time(const Time &o);
    explicit Time(const char * str);
    ~Time() = default;

    operator std::string() const;
    friend std::ostream &operator<<(std::ostream &os, const Time &time);

    Time &operator+=(int mins);
    Time &operator-=(int mins);
    Time operator+(int mins) const;
    Time operator-(int mins) const;

    friend bool operator==(const Time &lhs, const Time &rhs);
    friend bool operator!=(const Time &lhs, const Time &rhs);
    friend bool operator<(const Time &lhs, const Time &rhs);
    friend bool operator>(const Time &lhs, const Time &rhs);
    friend bool operator<=(const Time &lhs, const Time &rhs);
    friend bool operator>=(const Time &lhs, const Time &rhs);

    friend int operator-(const Time &lhs, const Time &rhs);
};

}  // namespace trainsys

#endif  // LIBTRAIN_DATETIME_H_