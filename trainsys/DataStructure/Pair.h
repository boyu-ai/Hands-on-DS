#ifndef PAIR_H
#define PAIR_H

namespace trainsys {

template <class FirstType, class SecondType>
struct Pair {
    FirstType first;
    SecondType second;

    Pair() {}
    Pair(const FirstType &first, const SecondType &second)
        : first(first), second(second) {}
};

template <class FirstType, class SecondType>
bool checkPairLess(const Pair<FirstType, SecondType> &lhs, const Pair<FirstType, SecondType> &rhs) {
    if (lhs.first != rhs.first) {
        return lhs.first < rhs.first;
    } else {
        return lhs.second < rhs.second;
    }
}

template <class FirstType, class SecondType>
bool checkPairEqual(const Pair<FirstType, SecondType> &lhs, const Pair<FirstType, SecondType> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

}

#endif