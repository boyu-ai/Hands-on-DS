#include <cassert>
#include <iostream>

#include "BPlusTree.h"
#include "List.h"
#include "Pair.h"

const int N = 1000;

// 请注意，B+树在运行时，会生成一些存放数据的文件
// 如果程序正常终止，下次运行时会自动加载这些文件中的数据
// 在调试B+树代码时，如果程序出现异常终止，你需要先删除B+树生成的数据文件再重新运行
void runTest1() {
  BPlusTree<int, int> bpt("test");
  for (int i = 1; i <= N; ++i) { bpt.insert(i, i); }
  int cnt = 0;
  for (int i = 1; i <= N; ++i) {
    int val;
    bool found = bpt.find(i, val);
    cnt += found;
  }
  assert(cnt == N);
  for (int i = 2; i <= N; i += 2) { bpt.remove(i); }
  cnt = 0;
  for (int i = 1; i <= N; ++i) {
    int val;
    bool found = bpt.find(i, val);
    cnt += found;
  }
  assert(cnt == N / 2);
  for (int i = 3; i <= N; i += 3) { bpt.remove(i); }
  cnt = 0;
  for (int i = 1; i <= N; ++i) {
    int val;
    bool found = bpt.find(i, val);
    cnt += found;
  }
  assert(cnt == N - N / 2 - N / 3 + N / 6);
  for (int i = 1; i <= N; i += 100) {
    int val;
    bool found = bpt.find(i, val);
    if (found) {
      assert(val == i);
      assert(i % 2 != 0 && i % 3 != 0);
      std::cout << "key = " << i << ", value = " << val << std::endl;
    }
  }
  std::cout << "test1 passed" << std::endl;
}

// 还需要测试，重新打开的程序能否正确加载磁盘中的数据
// runTest1()中的B+树已经析构，这里重新构造一个B+树，然后从磁盘中加载数据
void runTest2() {
  BPlusTree<int, int> bpt("test");
  int cnt = 0;
  for (int i = 1; i <= N; ++i) {
    int val;
    bool found = bpt.find(i, val);
    cnt += found;
  }
  assert(cnt == N - N / 2 - N / 3 + N / 6);
  for (int i = 1; i <= N; i += 100) {
    int val;
    bool found = bpt.find(i, val);
    if (found) {
      assert(val == i);
      assert(i % 2 != 0 && i % 3 != 0);
      std::cout << "key = " << i << ", value = " << val << std::endl;
    }
  }
  std::cout << "test2 passed" << std::endl;
}

// 输出所有的key和value
void runTest3() {
  BPlusTree<int, int> bpt("test");
  std::cout << "traversing B+ tree" << std::endl;
  bpt.traverse();
  std::cout << "traverse finished" << std::endl;
}

int main() {
  runTest1();
  runTest2();
  runTest3();
  return 0;
}