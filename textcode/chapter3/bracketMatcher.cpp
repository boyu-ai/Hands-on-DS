// 代码清单3-21 括号匹配样例代码
#include <cstring>
#include <iostream>

#include "seqStack.h"
using namespace std;

int main() {
  std::string s;
  cin >> s;
  seqStack<char> bracket;  // 用一个栈存储左括号
  for (int i = 0; i < s.length(); i++) {
    char cur = s[i];
    if (cur == ']' || cur == ')' || cur == '}') {
      // 下一个字符是右括号时
      if (bracket.isEmpty()) {  // 栈为空
        cout << "false" << endl;
        return 0;
      }
      char prev = bracket.pop();  // 和栈顶的左括号做匹配
      if (((prev == '[') && (cur == ']')) ||
          ((prev == '(') && (cur == ')') || 
          ((prev == '{') && (cur == '}')))) {
        continue;
      } else {
        cout << "false" << endl;  // 左右括号不匹配，例如(}
        return 0;
      }
    } else if (cur == '[' || cur == '(' || cur == '{') {
      bracket.push(cur);  // 将左括号进栈
    }
  }
  if (bracket.isEmpty()) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }
}
