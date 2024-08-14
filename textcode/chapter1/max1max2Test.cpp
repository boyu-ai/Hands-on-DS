// 代码清单1-1 函数max1与max2的实现及其测试程序
// 输入序列长度n，乘数d，以及序列中的数字a[i]，输出序列中的最大值和d的乘积
// 样例输入：
// 5 2
// 2 3 -1 2 -3
// 样例输出：
// max1: 6
// max2: 6
#include <iostream>
using namespace std;
int max1(int array[], int size, int d) { 
  int max = 0, i; 
  for (i = 0; i < size; ++i) array[i] *= d; 
  for (i = 0; i < size; ++i) 
    if (array[i] > max) max = array[i]; 
  return max; 
}  

int max2(int array[], int size, int d) { 
  int max = 0, i; 
  for (i = 0; i < size; ++i) 
    if (array[i] > max) max = array[i]; 
  return max * d; 
} 

int main(){
    int n, d;
    cin >> n >> d;
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
        b[i] = a[i];
    }
    int start, end;
    cout << "max1:" << max1(a, n, d) << endl;
    cout << "max2:" << max2(b, n, d) << endl;
}
