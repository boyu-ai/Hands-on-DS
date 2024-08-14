#ifndef BINARY_SEARCH_TABLE_H_
#define BINARY_SEARCH_TABLE_H_

#include "Pair.h"
#include "List.h"

namespace trainsys {

template <class KeyType, class ValueType>
class BinarySearchTable : public seqList<Pair<KeyType, ValueType>> {

private:
    void quicksort(int l, int r) {
        if (l >= r) return;
        int i = l, j = r;
        Pair<KeyType, ValueType> pivot = this->data[l];
        while (i < j) {
            while (i < j && this->data[j].first >= pivot.first) j--;
            this->data[i] = this->data[j];
            while (i < j && this->data[i].first <= pivot.first) i++;
            this->data[j] = this->data[i];
        }
        this->data[i] = pivot;
        quicksort(l, i - 1);
        quicksort(i + 1, r);
    }

public:
    BinarySearchTable(int initSize = 10): seqList<Pair<KeyType, ValueType>>(initSize) {}
    ~BinarySearchTable() = default;

    void insertEntry(const KeyType &key, const ValueType &val) {
        this->insert(this->length(), Pair<KeyType, ValueType>(key, val));
    }

    ValueType find(const KeyType &key) const {
        int l = 0, r = this->currentLength - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (this->data[mid].first == key) return this->data[mid].second;
            else if (this->data[mid].first < key) l = mid + 1;
            else r = mid - 1;
        }
        return ValueType();
    }

    void sortEntry() {
        quicksort(0, this->currentLength - 1);
    }
};

}

#endif // BINARY_SEARCH_TABLE_H_