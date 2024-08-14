// 代码清单 6-20 UserManager 类的定义与实现
#ifndef USER_MANAGER_H_
#define USER_MANAGER_H_

#include <cstring>

#include "RedBlackTree.h"

namespace trainsys {

using UserID = long long;
const int MAX_TRAINID_LEN = 25;
const int MAX_USERNAME_LEN = 20;
const int MAX_PASSWORD_LEN = 30;

struct UserInfo {
  UserID userID;
  char username[MAX_USERNAME_LEN];
  char password[MAX_PASSWORD_LEN];
  int privilege;  // 数字越大，则购票优先级越高

  UserInfo() = default;
  UserInfo(UserID userID, const char *username, const char *password,
      int privilege);
  UserInfo(const UserInfo &rhs);
  ~UserInfo() = default;
};

UserInfo::UserInfo(UserID userID, const char *username,
    const char *password, int privilege) {
  this->userID = userID;
  this->privilege = privilege;
  memcpy(this->username, username, MAX_USERNAME_LEN);
  memcpy(this->password, password, MAX_PASSWORD_LEN);
}

UserInfo::UserInfo(const UserInfo &rhs) {
  this->userID = rhs.userID;
  this->privilege = rhs.privilege;
  memcpy(this->username, rhs.username, MAX_USERNAME_LEN);
  memcpy(this->password, rhs.password, MAX_PASSWORD_LEN);
}

class UserManager {
 private:
  RedBlackTree<UserID, UserInfo> userInfoTable;

 public:
  UserManager() = default;
  ~UserManager() = default;

  void insertUser(const UserID userID, const char *username,
      const char *password, const int privilege);
  UserInfo *findUser(const UserID &userID);
  void removeUser(const UserID &userID);
  void modifyUserPrivilege(const UserID &userID, int newPrivilege);
  void modifyUsername(const UserID &userID, const char *newUername);
  void modifyUserPassword(const UserID &userID, const char *newPassword);
};

void UserManager::insertUser(const UserID userID,
    const char *username, const char *password, const int privilege) {
  userInfoTable.insert(SET<UserID, UserInfo>(
      userID, UserInfo(userID, username, password, privilege)));
}

UserInfo *UserManager::findUser(const UserID &userID) {
  SET<UserID, UserInfo> *data = userInfoTable.find(userID);
  // 注意，获取键值对以后比较 value 的方式
  if (data == nullptr)
    return nullptr;
  else
    return &data->other;
}

void UserManager::removeUser(const UserID &userID) {
  userInfoTable.remove(userID);
}

void UserManager::modifyUserPrivilege(
    const UserID &userID, int newPrivilege) {
  SET<UserID, UserInfo> *data = userInfoTable.find(userID);
  if (data != nullptr) { data->other.privilege = newPrivilege; }
}

void UserManager::modifyUsername(
    const UserID &userID, const char *newUsername) {
  SET<UserID, UserInfo> *data = userInfoTable.find(userID);
  if (data != nullptr) {
    int len = strlen(newUsername);
    if (len > MAX_USERNAME_LEN) len = MAX_USERNAME_LEN;
    memcpy(data->other.username, newUsername, len);
    data->other.username[len] = '\0';
  }
}

void UserManager::modifyUserPassword(
    const UserID &userID, const char *newPassword) {
  SET<UserID, UserInfo> *data = userInfoTable.find(userID);
  if (data != nullptr) {
    int len = strlen(newPassword);
    if (len > MAX_PASSWORD_LEN) len = MAX_PASSWORD_LEN;
    memcpy(data->other.password, newPassword, len);
    data->other.password[len] = '\0';
  }
}

}  // namespace trainsys

#endif