// 哈夫曼树的测试程序（修改自代码清单4-11）
// 输入待编码字符及其对应的权值，可以获得其哈夫曼编码
// 样例输入：
// abcd
// 请输入字符对应的权值：
// a:1
// b:2
// c:3
// d:4
// 样例输出：
// a:011
// b:010
// c:00
// d:1
#include <cstring>
#include <iostream>

#include "hfTree.h"
using namespace std;

int main() {
  char ch[100];
  cin >> ch;
  int length = strlen(ch);
  int *w = new int[length];
  cout << "请输入字符对应的权值：\n";
  for (int i = 0; i < length; i++) {
    cout << ch[i] << ":";
    cin >> w[i];
  }
  hfTree<char> tree(ch, w, length);
  hfTree<char>::hfCode *result = new hfTree<char>::hfCode[length];

  tree.getCode(result);

  for (int i = 0; i < length; ++i)
    cout << result[i].data << ':' << result[i].code << endl;
  return 0;
}
