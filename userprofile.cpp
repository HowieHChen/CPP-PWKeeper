#include "userprofile.h"

UserProfile::UserProfile()
{
    INIActivated = new INIService;
    INIActivated->connectINI(userINIPath);
}

//读取所有用户名和配置信息
void UserProfile::readProfile()
{
    userAll.clear();
    userAll = INIActivated->getAllValue("UserList");
    lastName=INIActivated->getValue("Settings","LastName");
    lastPassword=INIActivated->getValue("Settings","LastPassword");
    lastMail=INIActivated->getValue(lastName,"Mail");
    if(INIActivated->getValue("Settings","SaveLastName")=="True" ||
       INIActivated->getValue("Settings","SaveLastName")=="true" )
    {
        saveLastName = true;
    }
    else
    {
        saveLastName = false;
    }
    if(INIActivated->getValue("Settings","SaveLastPassword")=="True" ||
       INIActivated->getValue("Settings","SaveLastPassword")=="true" )
    {
        saveLastPassword = true;
    }
    else
    {
        saveLastPassword = false;
    }
    if(INIActivated->getValue("Settings","CloseDirectly")=="True" ||
       INIActivated->getValue("Settings","CloseDirectly")=="true" )
    {
        closeDirectly = true;
    }
    else
    {
        closeDirectly = false;
    }
}

void UserProfile::saveProfile()
{
    INIActivated->setValue("Settings","LastName",lastName);
    INIActivated->setValue("Settings","LastPassword",lastPassword);
}

void UserProfile::saveSettings()
{
    INIActivated->setValue("Settings","SaveLastName",(saveLastName?"True":"False"));
    INIActivated->setValue("Settings","saveLastPassword",(saveLastPassword?"True":"False"));
    INIActivated->setValue("Settings","closeDirectly",(closeDirectly?"True":"False"));
}

//返回所有用户名
QStringList UserProfile::getAllUser()
{
    return userAll;
}

//返回上次登录用户名
QString UserProfile::getLastName()
{
    return lastName;
}

//返回上次登陆密码
QString UserProfile::getLastPassword()
{
    return lastPassword;
}

//返回上次登陆密码
QString UserProfile::getLastMail()
{
    return lastMail;
}

//用户登录
bool UserProfile::userSignIn(QString tName,QString tPassword)
{
    qDebug()<<"userSignIn";
    if(userAll.contains(tName))
    {
        if(INIActivated->getValue(tName,"Password")==tPassword)
        {
            lastName = tName;
            lastPassword = tPassword;
            saveProfile();
            qDebug()<<"success";
            return true;
        }
    }
    qDebug()<<"failure";
    return false;
}

//用户重设密码
bool UserProfile::userResetPW(QString tName,QString tOldPassword,QString tNewPassword)
{
    if(userAll.contains(tName))
    {
        if(INIActivated->getValue(tName,"Password")==tOldPassword)
        {
            INIActivated->setValue(tName,"Password",tNewPassword);
            lastName = "";
            lastPassword = "";
            return true;
        }
    }
    return false;
}

//用户忘记密码
bool UserProfile::userForgetPW(QString tName,QString tMail,QString tNewPassword)
{
    if(userAll.contains(tName))
    {
        if(INIActivated->getValue(tName,"Mail")==tMail)
        {
            INIActivated->setValue(tName,"Password",tNewPassword);
            lastName = "";
            lastPassword = "";
            return true;
        }
    }
    return false;
}

//用户注册
bool UserProfile::userSignUp(QString tName,QString tMail,QString tPassword)
{
    qDebug()<<"userSignUp";
    if(userAll.contains(tName))
    {
        qDebug()<<"userSignUp Failure, user exist";
        return false;
    }
    else
    {
        qDebug()<<"userSignUp done";
        INIActivated->setValue("UserList",tName,"1");
        INIActivated->setValue(tName,"Name",tName);
        INIActivated->setValue(tName,"Password",tPassword);
        INIActivated->setValue(tName,"Mail",tMail);
        readProfile();
        return true;
    }
}

bool UserProfile::userExist(QString tName)
{
    return userAll.contains(tName);
}

bool UserProfile::mailCheck(QString tName, QString tMail)
{
    if(!userExist(tName))
    {
        return false;
    }
    bool tResult=(INIActivated->getValue(tName,"Mail")==tMail);
    return tResult;
}
