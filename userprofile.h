#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QString>

#include "iniservice.h"

class UserProfile
{
public:
    UserProfile();

    INIService *INIActivated;

    //记录用户设置
    bool saveLastName;
    bool saveLastPassword;
    bool closeDirectly;

    //读取所有用户信息和设置
    void readProfile();

    //保存登录信息
    void saveProfile();

    //保存设置
    void saveSettings();

    //获取所有用户列表
    QStringList getAllUser();

    //获取最后登录用户信息
    QString getLastName();
    QString getLastPassword();
    QString getLastMail();

    //用户登录
    bool userSignIn(QString tName,QString tPassword);

    //用户修改密码
    bool userResetPW(QString tName,QString tOldPassword,QString tNewPassword);

    //用户重置密码
    bool userForgetPW(QString tName,QString tMail,QString tNewPassword);

    //用户注册
    bool userSignUp(QString tName,QString tMail,QString tPassword);

    //查询用户是否存在
    bool userExist(QString tName);

    //查询邮箱是否匹配
    bool mailCheck(QString tName,QString tMail);

private:
    //用户配置文件路径
    const QString userINIPath="/INI/UserProfile.ini";

    //用户列表
    QStringList userAll;

    //当前登录用户信息
    QString lastName;
    QString lastPassword;
    QString lastMail;

};

#endif // USERPROFILE_H
