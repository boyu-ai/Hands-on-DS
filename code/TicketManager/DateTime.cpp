#include "DateTime.h"

namespace trainsys {

Date::Date(int mon, int mday) : mon(mon), mday(mday) {}

Date::Date(const char * str) {
    mon = (str[0] - '0') * 10 + str[1] - '0';
    mday = (str[3] - '0') * 10 + str[4] - '0';
}

Date &Date::operator+=(int mdays) {
    mday += mdays;
    while (mday > mday_number_[mon]) mday -= mday_number_[mon++];
    return *this;
}
Date &Date::operator-=(int mdays) {
    mday -= mdays;
    while (mday <= 0) mday += mday_number_[--mon];
    return *this;
}
Date Date::operator+(int mdays) {
    Date ret(*this);
    ret += mdays;
    return ret;
}
Date Date::operator-(int mdays) {
    Date ret(*this);
    ret -= mdays;
    return ret;
}

Date::operator std::string() const {
    std::string ret = "";
    ret = static_cast<char>('0' + mon % 10) + ret;
    ret = static_cast<char>('0' + mon / 10) + ret;
    ret = ret + '-';
    ret = ret + static_cast<char>('0' + mday / 10);
    ret = ret + static_cast<char>('0' + mday % 10);
    return ret;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.mon / 10 << date.mon % 10;
    os << '-';
    os << date.mday / 10 << date.mday % 10;
    return os;
}

bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.mon == rhs.mon && lhs.mday == rhs.mday;
}
bool operator!=(const Date &lhs, const Date &rhs) {
    return lhs.mon != rhs.mon || lhs.mday != rhs.mday;
}
bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.mon != rhs.mon) return lhs.mon < rhs.mon;
    return lhs.mday < rhs.mday;
}
bool operator>(const Date &lhs, const Date &rhs) {
    if (lhs.mon != rhs.mon) return lhs.mon > rhs.mon;
    return lhs.mday > rhs.mday;
}
bool operator<=(const Date &lhs, const Date &rhs) {
    if (lhs.mon != rhs.mon) return lhs.mon < rhs.mon;
    return lhs.mday <= rhs.mday;
}
bool operator>=(const Date &lhs, const Date &rhs) {
    if (lhs.mon != rhs.mon) return lhs.mon > rhs.mon;
    return lhs.mday >= rhs.mday;
}
int operator-(const Date &lhs, const Date &rhs) {
    int mdays = prefix_total_[lhs.mon - 1] - prefix_total_[rhs.mon - 1];
    return mdays + lhs.mday - rhs.mday;
}

Time::Time(int min, int hour, int mday, int mon, int year)
    : min(min), hour(hour), date(mon, mday) {}

Time::Time(const Time &o) : min(o.min), hour(o.hour), date(o.date) {}

Time::Time(const char * str) {
    hour = (str[0] - '0') * 10 + str[1] - '0';
    min = (str[3] - '0') * 10 + str[4] - '0';
}

Time::operator std::string() const {
    std::string ret = "";
    ret += '0' + hour / 10;
    ret += '0' + hour % 10;
    ret += ':';
    ret += '0' + min / 10;
    ret += '0' + min % 10;
    return ret;
}

std::ostream &operator<<(std::ostream &os, const Time &time) {
    os << time.hour / 10 << time.hour % 10;
    os << ':';
    os << time.min / 10 << time.min % 10;
    return os;
}

Time &Time::operator+=(int mins) {
    min += mins;
    if (min >= 60) {
        hour += min / 60, min %= 60;
        if (hour >= 24) date += hour / 24, hour %= 24;
    }
    return *this;
}
Time &Time::operator-=(int mins) {
    min -= mins;
    if (min < 0) {
        int tmp = (-min + 59) / 60;
        hour -= tmp, min += 60 * tmp;
        if (hour < 0) {
            tmp = (-hour + 23) / 24;
            date -= tmp, hour += 24 * tmp;
        }
    }
    return *this;
}

Time Time::operator+(int mins) const {
    Time ret(*this);
    ret += mins;
    return ret;
}
Time Time::operator-(int mins) const {
    Time ret(*this);
    ret -= mins;
    return ret;
}

bool operator==(const Time &lhs, const Time &rhs) {
    return lhs.hour == rhs.hour && lhs.min == rhs.min && lhs.date == rhs.date;
}
bool operator!=(const Time &lhs, const Time &rhs) {
    return lhs.hour != rhs.hour || lhs.min != rhs.min || lhs.date != rhs.date;
}
bool operator<(const Time &lhs, const Time &rhs) {
    if (lhs.date != rhs.date) return lhs.date < rhs.date;
    if (lhs.hour != rhs.hour) return lhs.hour < rhs.hour;
    return lhs.min < rhs.min;
}
bool operator>(const Time &lhs, const Time &rhs) {
    if (lhs.date != rhs.date) return lhs.date > rhs.date;
    if (lhs.hour != rhs.hour) return lhs.hour > rhs.hour;
    return lhs.min > rhs.min;
}
bool operator<=(const Time &lhs, const Time &rhs) {
    if (lhs.date != rhs.date) return lhs.date < rhs.date;
    if (lhs.hour != rhs.hour) return lhs.hour < rhs.hour;
    return lhs.min <= rhs.min;
}
bool operator>=(const Time &lhs, const Time &rhs) {
    if (lhs.date != rhs.date) return lhs.date > rhs.date;
    if (lhs.hour != rhs.hour) return lhs.hour > rhs.hour;
    return lhs.min >= rhs.min;
}

int operator-(const Time &lhs, const Time &rhs) {
    int mins = (lhs.date - rhs.date) * 1440;
    mins += (lhs.hour - rhs.hour) * 60;
    return mins + lhs.min - rhs.min;
}

}  // namespace trainsys
