#include "UserManager.h"

namespace trainsys {

UserManager::UserManager(const char* filename): userInfoTable(filename) {}

void UserManager::insertUser(const UserID &userID, const char *username, const char* password, int privilege) {
    userInfoTable.insert(userID, UserInfo(userID, username, password, privilege));
}

bool UserManager::existUser(const UserID &userID) {
    return userInfoTable.contains(userID);
}

UserInfo UserManager::findUser(const UserID &userID) {
    return userInfoTable.find(userID);
}

void UserManager::removeUser(const UserID &userID) {
    userInfoTable.remove(userID);
}

void UserManager::modifyUserPrivilege(const UserID &userID, int newPrevilege) {
    UserInfo userInfo = userInfoTable.find(userID);
    userInfo.privilege = newPrevilege;

    userInfoTable.remove(userID);
    userInfoTable.insert(userID, userInfo);
}

void UserManager::modifyUserPassword(const UserID &userID, const char* newPassword) {
    UserInfo userInfo = userInfoTable.find(userID);    
    int len = strlen(newPassword);
    if (len > MAX_PASSWORD_LEN) len = MAX_PASSWORD_LEN;
    memcpy(userInfo.password, newPassword, len);
    userInfo.password[len] = '\0';

    userInfoTable.remove(userID);
    userInfoTable.insert(userID, userInfo);
}


} // namespace trainsys