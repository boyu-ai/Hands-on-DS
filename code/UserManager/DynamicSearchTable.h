#ifndef SEARCH_TABLE_H_
#define SEARCH_TABLE_H_

namespace trainsys {

template <class KEY, class OTHER>
struct SET {
  KEY key;
  OTHER other;
  SET(KEY k, OTHER o) {
    key = k;
    other = o;
  }
  SET() = default;
};

template <class KEY, class OTHER>
class DynamicSearchTable {
 public:
  virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
  virtual void insert(const SET<KEY, OTHER> &x) = 0;
  virtual void remove(const KEY &x) = 0;
  virtual ~DynamicSearchTable() {};
};

}  // namespace trainsys

#endif