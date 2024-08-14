#ifndef PAIR_H
#define PAIR_H

template <class FirstType, class SecondType>
struct Pair {
  FirstType first;
  SecondType second;

  Pair() {}
  Pair(const FirstType &first, const SecondType &second)
      : first(first), second(second) {}
  bool operator<(const Pair &rhs) const {
    if (first != rhs.first) {
      return first < rhs.first;
    } else {
      return second < rhs.second;
    }
  }
  bool operator==(const Pair &rhs) const {
    return first == rhs.first && second == rhs.second;
  }
  bool operator!=(const Pair &rhs) const { return !(*this == rhs); }
  bool operator>(const Pair &rhs) const { return rhs < *this; }
  bool operator<=(const Pair &rhs) const { return !(*this > rhs); }
  bool operator>=(const Pair &rhs) const { return !(*this < rhs); }
};

#endif