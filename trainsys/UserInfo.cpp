#include "UserInfo.h"

namespace trainsys {
    
UserInfo::UserInfo(UserID userID, const char* username, const char *password, int privilege) {
    this->userID = userID;
    this->privilege = privilege;
    int len = strlen(username);
    if (len > MAX_USERNAME_LEN) len = MAX_USERNAME_LEN;
    memcpy(this->username, username, len);
    this->username[len] = '\0';
    len = strlen(password);
    if (len > MAX_PASSWORD_LEN) len = MAX_PASSWORD_LEN;
    memcpy(this->password, password, len);
    this->password[len] = '\0';
}

UserInfo::UserInfo(const UserInfo &rhs) {
    this->userID = rhs.userID;
    this->privilege = rhs.privilege;
    memcpy(this->username, rhs.username, MAX_USERNAME_LEN + 1);
    memcpy(this->password, rhs.password, MAX_PASSWORD_LEN + 1);
}

UserInfo& UserInfo::operator = (const UserInfo &rhs) {
    if (this != &rhs) {
        this->userID = rhs.userID;
        this->privilege = rhs.privilege;
        memcpy(this->username, rhs.username, MAX_USERNAME_LEN + 1);
        memcpy(this->password, rhs.password, MAX_PASSWORD_LEN + 1);
    }
    return *this;
}

bool UserInfo::operator == (const UserInfo &rhs) const {
    return userID == rhs.userID;
}

bool UserInfo::operator != (const UserInfo &rhs) const {
    return userID != rhs.userID;
}

bool UserInfo::operator < (const UserInfo &rhs) const {
    return userID < rhs.userID;
}

} // namespace trainsys
