#ifndef USERINFO_H_
#define USERINFO_H_

#include "Utils.h"

namespace trainsys {

struct UserInfo {
    UserID userID;
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    int privilege;  // 数字越大，排队购票优先级越高

    UserInfo() = default;
    UserInfo(UserID userID, const char* username, const char* password, int privilege);
    UserInfo(const UserInfo &rhs);
    ~UserInfo() = default;

    UserInfo& operator = (const UserInfo &rhs);
    bool operator == (const UserInfo &rhs) const;
    bool operator != (const UserInfo &rhs) const;
    bool operator < (const UserInfo &rhs) const;
};

}

#endif 