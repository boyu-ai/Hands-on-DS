// 开哈希表的测试程序
// 和std库中的map对照随机插入、删除后的结果，如果结果一致，则输出测试通过，否则测试失败。
// 注意，插入数据时需避免重复键值。
// 输出样例：
// Insertion test passed.
// Removal test passed.

#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

#include "openHashTable.h"

using my_table_t = openHashTable<int, int>;
using std_table_t = map<int, int>;

const int N = 50, M = 10, W = 50;
int my_insert_binmap[50] = {0};

// 查找测试
bool runLookupTest(my_table_t &my_table, std_table_t &std_table) {
  for (int i = 0; i < M; ++i) {
    int x = rand() % W;
    auto my_lookup = my_table.find(x);
    auto std_lookup = std_table.find(x);
    if (my_lookup != nullptr && std_lookup == std_table.end()) {
      std::cout << "unexpected key was found: " << x << std::endl;
      return false;
    }
    if (my_lookup == nullptr && std_lookup != std_table.end()) {
      std::cout << "expected key was not found: " << x << std::endl;
      return false;
    }
    if (std_lookup == std_table.end()) continue;
    if (std_lookup->second != my_lookup->other) {
      std::cout << "differ in value for key " << x << std::endl;
      return false;
    }
  }
  return true;
}

// 插入测试
bool runInsertionTest(my_table_t &my_table, std_table_t &std_table) {
  for (int i = 0; i < N; ++i) {
    int x = rand() % W;
    if (my_insert_binmap[x] == 1) {
      std::cout << "insert #" << i << ": " << x << " already exists, skip.\n";
      continue;
    }
    my_insert_binmap[x] = 1;
    std::cout << "insert #" << i << ": " << x << "\n";
    my_table.insert(SET<int, int>(x, 2 * x + 1));
    std_table.insert(make_pair(x, 2 * x + 1));
    if (!runLookupTest(my_table, std_table)) return false;
  }
  return true;
}

// 删除测试
bool runRemovalTest(my_table_t &my_table, std_table_t &std_table) {
  for (int i = 0; i < N; ++i) {
    int x = rand() % W;
    std::cout << "remove #" << i << ", " << x << "\n";
    my_table.remove(x);
    std_table.erase(x);
    if (!runLookupTest(my_table, std_table)) return false;
  }
  return true;
}

int main() {
  srand(time(0));
  openHashTable<int, int> my_table;
  std_table_t std_table;

  if (runInsertionTest(my_table, std_table)) {
    std::cout << "Insertion test passed.\n" << std::endl;
  } else {
    std::cout << "Insertion test failed.\n" << std::endl;
    return 0;
  }

  if (runRemovalTest(my_table, std_table)) {
    std::cout << "Removal test passed.\n" << std::endl;
  } else {
    std::cout << "Removal test failed.\n" << std::endl;
    return 0;
  }

  return 0;
}