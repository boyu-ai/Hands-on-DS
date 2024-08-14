// 代码清单11-3　求解八皇后问题的程序
// 寻找棋盘八皇后问题
// 样例输出：
// 1: 1	2: 5	3: 8	4: 6	5: 3	6: 7	7: 2	8: 4
#include <iostream>
using namespace std;
void queen_all(int k);
int col[9];

bool row[9], digLeft[16], digRight[16];
// 在8*8的棋盘的第k列上找合理的配置

void queen_all(int k) {
  int i, j;
  char awn;                // 保存是否需要继续寻找的标志
  for (i = 1; i < 9; i++)  // 依次在l～8行上配置k列的皇后
    if (row[i] && digLeft[k + i - 1] && digRight[8 + k - i]) {
      // 可行位置
      col[k] = i;
      // 对应位置有皇后
      row[i] = digLeft[k + i - 1] = digRight[8 + k - i] = false;

      if (k == 8) {  // 找到一个可行解
        for (j = 1; j <= 8; j++) cout << j << ": " << col[j] << '\t';
        cout << endl << "是否需要继续寻找（按Q退出，按其他键继续：）";
        cin >> awn;
        if (awn == 'Q' || awn == 'q') exit(0);
      } else
        queen_all(k + 1);  // 递归至第k+1列
      // 恢复对应位置无皇后的状态
      row[i] = digLeft[k + i - 1] = digRight[8 + k - i] = true;
    }
}

int main() {
  int j;
  for (j = 0; j <= 8; j++) row[j] = true;
  for (j = 0; j < 16; j++) digLeft[j] = digRight[j] = true;
  queen_all(1);
  return 0;
}