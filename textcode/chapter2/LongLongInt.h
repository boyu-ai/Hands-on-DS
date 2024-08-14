// 代码清单2-9至2-13 大整数类 LongLongInt的定义和实现
#ifndef CHAPTER2_LONGLONGINT_H
#define CHAPTER2_LONGLONGINT_H

#include <cstring>
#include <iostream>
using namespace std;

class LongLongInt {
  friend LongLongInt operator+(const LongLongInt &, const LongLongInt &);
  friend LongLongInt operator-(const LongLongInt &, const LongLongInt &);
  friend ostream &operator<<(ostream &, const LongLongInt &);

 private:
  char sign;
  char *num;

 public:
  LongLongInt(const char *n = "");
  LongLongInt(const LongLongInt &);
  LongLongInt &operator=(const LongLongInt &);
  ~LongLongInt() { delete num; }
};

bool ngreater(const char *s1, const char *s2);
char *add(const char *s1, const char *s2);
char *sub(const char *s1, const char *s2);

LongLongInt::LongLongInt(const char *n) {
  const char *tmp;  // 保存参数n的绝对值
  // 处理正负符号位
  switch (n[0]) {
    case '+':
      sign = '+';
      tmp = n + 1;
      break;
    case '-':
      sign = '-';
      tmp = n + 1;
      break;
    default:
      sign = '+';
      tmp = n;
  }

  if (strcmp(tmp, "0") == 0) tmp = "";
  int len = strlen(tmp);

  num = new char[len + 1];
  for (int i = 0; i < len; ++i) num[len - i - 1] = tmp[i];
  num[len] = '\0';
}

LongLongInt::LongLongInt(const LongLongInt &other) {
  sign = other.sign;
  num = new char[strlen(other.num) + 1];
  strcpy(num, other.num);
}

LongLongInt &LongLongInt::operator=(const LongLongInt &right) {
  if (this == &right) return *this;

  delete num;
  sign = right.sign;
  num = new char[strlen(right.num) + 1];
  strcpy(num, right.num);
  return *this;
}

ostream &operator<<(ostream &os, const LongLongInt &obj) {
  if (strlen(obj.num) == 0)
    os << 0;
  else {
    os << obj.sign;
    for (int i = strlen(obj.num) - 1; i >= 0; --i) os << obj.num[i];
  }
  return os;
}

LongLongInt operator+(const LongLongInt &n1, const LongLongInt &n2) {
  LongLongInt n;  // 存储加的结果值

  delete n.num;
  if (n1.sign == n2.sign) {
    n.sign = n1.sign;
    n.num = add(n1.num, n2.num);
  } else if (ngreater(n1.num, n2.num)) {
    n.sign = n1.sign;
    n.num = sub(n1.num, n2.num);
  } else {
    n.sign = n2.sign;
    n.num = sub(n2.num, n1.num);
  }
  return n;
}

LongLongInt operator-(const LongLongInt &n1, const LongLongInt &n2) {
  // 复制被减数n2至新大整数对象n，翻转n的正负符号并将n作为被加数
  LongLongInt n(n2);

  if (n.sign == '+')
    n.sign = '-';
  else
    n.sign = '+';

  return n1 + n;
}

char *add(const char *s1, const char *s2) {
  int len1 = strlen(s1), len2 = strlen(s2);
  int minLen = (len1 > len2 ? len2 : len1);
  int len = (len1 > len2 ? len1 : len2) + 1;
  int carry = 0, result;              // carry：进位
  char *num = new char[len + 1];      // 保存运算结果值
  int i = 0;
  for (; i < minLen; ++i) {           // 两个加数对应的位都存在
    result = s1[i] - '0' + s2[i] - '0' + carry;
    num[i] = result % 10 + '0';
    carry = result / 10;
  }

  while (i < len1) {  // n2结束
    result = s1[i] - '0' + carry;
    num[i] = result % 10 + '0';
    carry = result / 10;
    ++i;
  }

  while (i < len2) {  // n1结束
    result = s2[i] - '0' + carry;
    num[i] = result % 10 + '0';
    carry = result / 10;
    ++i;
  }

  if (carry != 0) num[i++] = carry + '0';  // 处理最后的进位
  num[i] = '\0';

  return num;
}

char *sub(const char *s1, const char *s2) {
  char* zero = new char[1];
  zero[0] = '\0';
  if (!strcmp(s1, s2)) return zero;  // 两个数字相同，结果值为0
  int len1 = strlen(s1), len2 = strlen(s2);
  int minus = 0;                    // 借位
  char *tmp = new char[len1 + 1];   // 存储运算结果值
  int i = 0;
  for (; i < len2; ++i) {           // 两个数字对应的位都存在
    tmp[i] = s1[i] - s2[i] - minus;
    if (tmp[i] < 0) {
      tmp[i] += 10;
      minus = 1;
    } else
      minus = 0;
    tmp[i] += '0';  // 替换成字符
  }

  while (i < len1) {  // 处理n1剩余的位数
    tmp[i] = s1[i] - '0' - minus;
    if (tmp[i] < 0) {
      tmp[i] += 10;
      minus = 1;
    } else
      minus = 0;
    tmp[i] += '0';
    ++i;
  }

  do {  // 压缩运算结果值中的高位0
    --i;
  } while (i >= 0 && tmp[i] == '0');
  tmp[i + 1] = '\0';
  return tmp;
}

bool ngreater(const char *s1, const char *s2) {
  int len1 = strlen(s1), len2 = strlen(s2);
  if (len1 > len2)
    return true;  // 位数多者较大
  else if (len1 < len2)
    return false;
  for (int i = len1 - 1; i >= 0; --i) {
    // 位数相同，从高位到低位依次比较每一位
    if (s1[i] > s2[i])
      return true;
    else if (s1[i] < s2[i])
      return false;
  }
  return false;
}

#endif  // CHAPTER2_LONGLONGINT_H
