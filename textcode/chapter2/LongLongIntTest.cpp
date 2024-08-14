// LongLongInt类的测试程序
// 输入两个大整数（位数不超过100），输出其对应的a+b和a-b
// 样例输入：124 421
// 样例输出： a plus b is +545
//          a minus b is -297
#include "LongLongInt.h"
int main() {
  char a[100], b[100];
  cin >> a >> b;
  LongLongInt inta(a), intb(b);
  LongLongInt intc(inta);
  cout << "a plus b is " << inta + intb << endl;
  cout << "a minus b is " << intc - intb << endl;
}