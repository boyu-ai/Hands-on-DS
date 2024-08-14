// 代码清单4-19　PurchaseInfo 类
#ifndef PURCHASEINFO_H_
#define PURCHASEINFO_H_

#include "DateTime.h"
#include "PrioritizedWaitingList.h"
#include "Utils.h"

namespace trainsys {

class User {  // 用户类
 private:
  char username[20];
  char password[30];
  char mailAddr[30];
  int privilege;

 public:
  // User类的默认构造函数
  User() {
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    memset(mailAddr, 0, sizeof(mailAddr));
    privilege = 0;
  }

  // User类的构造函数
  User(
      char *username, char *password, char *mailAddr, int privilege) {
    strcpy(this->username, username);
    strcpy(this->password, password);
    strcpy(this->mailAddr, mailAddr);
    this->privilege = privilege;
  }

  // User类的拷贝构造函数
  User(const User &rhs) {
    strcpy(username, rhs.username);
    strcpy(password, rhs.password);
    strcpy(mailAddr, rhs.mailAddr);
    privilege = rhs.privilege;
  }

  ~User() {}

  const char *getName() const { return username; }
  const int getPrivilege() const { return privilege; }

  // 重载赋值运算符
  User &operator=(const User &rhs) {
    strcpy(username, rhs.username);
    strcpy(password, rhs.password);
    strcpy(mailAddr, rhs.mailAddr);
    privilege = rhs.privilege;
    return *this;
  }
};

struct PurchaseInfo {
  User user;
  TrainID trainID;
  Date date;
  StationID departureStation;
  int type;  // 1表示购票，-1表示退票

  PurchaseInfo() = default;
  PurchaseInfo(const User &user, const TrainID &trainID,
      const Date &date, const StationID &departureStation, int type) {
    this->user = user;
    this->trainID = trainID;
    this->date = date;
    this->departureStation = departureStation;
    this->type = type;
  }
  ~PurchaseInfo() = default;

  bool isOrdering() const { return type >= 0; }
  bool isRefunding() const { return type < 0; }

  const User getUser() const { return user; }
  const Date getDate() const { return date; }
  const StationID getDepartureStation() const {
    return departureStation;
  }

  PurchaseInfo &operator=(const PurchaseInfo &rhs) {
    user = rhs.user;
    trainID = rhs.trainID;
    date = rhs.date;
    departureStation = rhs.departureStation;
    type = rhs.type;
    return *this;
  }

  // 重载比较运算符
  bool operator<(const PurchaseInfo &rhs) const {
    int p1 = getUser().getPrivilege();
    int p2 = rhs.getUser().getPrivilege();
    if (p1 > p2)
      return true;
    else if (p1 == p2)
      return date < rhs.date;
    return false;
  }
};

}  // namespace trainsys

#endif