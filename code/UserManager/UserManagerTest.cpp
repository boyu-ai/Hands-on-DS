// UserManager 类的测试程序
// 编译命令：g++ UserManagerTest.cpp -o code.out
// 样例输出：
// Printint info of user with ID = 99:
// UserID: 99
// Username: User99
// Password: Psd99
// Privilege: 99
// Test_UserManager passed.
#include <cassert>
#include <iostream>

#include "UserManager.h"

int main() {
  trainsys::UserManager userManager;
  for (int i = 1; i <= 99; i += 2) {
    char *username = new char[10];
    char *password = new char[10];
    sprintf(username, "User%d", i);
    sprintf(password, "Psd%d", i);
    userManager.insertUser(i, username, password, i);
  }
  for (int i = 100; i >= 2; i -= 2) {
    char *username = new char[10];
    char *password = new char[10];
    sprintf(username, "User%d", i);
    sprintf(password, "Psd%d", i);
    userManager.insertUser(i, username, password, i);
  }
  for (int i = 1; i <= 100; ++i) {
    trainsys::UserInfo *userInfo = userManager.findUser(i);
    // 如果assert()的参数为false，则程序会终止
    assert(userInfo != nullptr && userInfo->userID == i);
  }
  for (int i = 2; i <= 100; i += 2) { userManager.removeUser(i); }
  for (int i = 1; i <= 100; ++i) {
    trainsys::UserInfo *userInfo = userManager.findUser(i);
    if (i % 2 == 0) {
      assert(userInfo == nullptr);
    } else {
      assert(userInfo != nullptr && userInfo->userID == i);
    }
  }
  trainsys::UserInfo *userInfo = userManager.findUser(99);
  assert(userInfo != nullptr);
  std::cout << "Printint info of user with ID = 99:" << std::endl;
  assert(userInfo->userID == 99);
  std::cout << "UserID: " << userInfo->userID << std::endl;
  assert(strcmp(userInfo->username, "User99") == 0);
  std::cout << "Username: " << userInfo->username << std::endl;
  assert(strcmp(userInfo->password, "Psd99") == 0);
  std::cout << "Password: " << userInfo->password << std::endl;
  assert(userInfo->privilege == 99);
  std::cout << "Privilege: " << userInfo->privilege << std::endl;
  std::cout << "Test_UserManager passed." << std::endl;
  return 0;
}