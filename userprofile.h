#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QString>

#include "iniservice.h"

class UserProfile
{
public:
    UserProfile();

    INIService *INIActivated;

    bool saveLastName;
    bool saveLastPassword;
    bool closeDirectly;

    void readAllUser();
    QStringList getAllUser();
    QString getLastName();
    QString getLastPassword();

    bool userSignIn(QString tName,QString tPassword);
    bool userResetPW(QString tName,QString tOldPassword,QString tNewPassword);
    bool userForgetPW(QString tName,QString tMail,QString tNewPassword);
    bool userSignUp(QString tName,QString tMail,QString tPassword);
    bool userExist(QString tName);
    bool mailCheck(QString tName,QString tMail);
private:
    const QString userINIPath="/INI/UserProfile.ini";

    QStringList userAll;
    QString userName;
    QString userPassword;
    QString lastName;
    QString lastPassword;
};

#endif // USERPROFILE_H
