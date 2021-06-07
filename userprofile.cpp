#include "userprofile.h"

UserProfile::UserProfile()
{
    //连接用户配置文件
    INIActivated = new INIService;
    INIActivated->connectINI(userINIPath);
}

//读取所有用户信息和设置
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
    //为统一使用INIService进行文件操作，所有键值均为文本
}

//保存登录信息
void UserProfile::saveProfile()
{
    INIActivated->setValue("Settings","LastName",lastName);
    INIActivated->setValue("Settings","LastPassword",lastPassword);
}

//保存设置
void UserProfile::saveSettings()
{
    INIActivated->setValue("Settings","SaveLastName",(saveLastName?"True":"False"));
    INIActivated->setValue("Settings","saveLastPassword",(saveLastPassword?"True":"False"));
    INIActivated->setValue("Settings","closeDirectly",(closeDirectly?"True":"False"));
}

//获取所有用户列表
QStringList UserProfile::getAllUser()
{
    return userAll;
}

//获取最后登录用户名
QString UserProfile::getLastName()
{
    return lastName;
}

//获取最后登录密码
QString UserProfile::getLastPassword()
{
    return lastPassword;
}

//获取最后登录邮箱
QString UserProfile::getLastMail()
{
    return lastMail;
}

//用户登录
bool UserProfile::userSignIn(QString tName,QString tPassword)
{
    //qDebug()<<"userSignIn";
    if(userAll.contains(tName))
    {
        if(INIActivated->getValue(tName,"Password")==tPassword)
        {
            lastName = tName;
            lastPassword = tPassword;
            saveProfile();
            //保存最后登录的用户的信息
            //qDebug()<<"userSignIn Done";
            return true;
        }
    }
    //qDebug()<<"userSignIn Failure, user doesn't exist";
    return false;
}

//用户修改密码
bool UserProfile::userResetPW(QString tName,QString tOldPassword,QString tNewPassword)
{
    //qDebug()<<"userResetPW";
    if(userAll.contains(tName))
    {
        if(INIActivated->getValue(tName,"Password")==tOldPassword)
        {
            INIActivated->setValue(tName,"Password",tNewPassword);
            lastName = "";
            lastPassword = "";
            //修改密码后移除保存的登录信息
            //qDebug()<<"userResetPW Done";
            return true;
        }
    }
    //qDebug()<<"userResetPW Failure, user doesn't exist";
    return false;
}

//用户重置密码
bool UserProfile::userForgetPW(QString tName,QString tMail,QString tNewPassword)
{
    //qDebug()<<"userForgetPW";
    if(userAll.contains(tName))
    {
        if(INIActivated->getValue(tName,"Mail")==tMail)
        {
            INIActivated->setValue(tName,"Password",tNewPassword);
            lastName = "";
            lastPassword = "";
            //重置密码后移除保存的登录信息
            //qDebug()<<"userForgetPW Done";
            return true;
        }
    }
    //qDebug()<<"userForgetPW Failure, user doesn't exist";
    return false;
}

//用户注册
bool UserProfile::userSignUp(QString tName,QString tMail,QString tPassword)
{
    //qDebug()<<"userSignUp";
    if(userAll.contains(tName))
    {
        //qDebug()<<"userSignUp Failure, user exists";
        return false;
    }
    else
    {
        INIActivated->setValue("UserList",tName,"1");
        INIActivated->setValue(tName,"Name",tName);
        INIActivated->setValue(tName,"Password",tPassword);
        INIActivated->setValue(tName,"Mail",tMail);
        readProfile();
        //qDebug()<<"userSignUp Done";
        return true;
    }
}

//查询用户是否存在
bool UserProfile::userExist(QString tName)
{
    return userAll.contains(tName);
}

//查询邮箱是否匹配
bool UserProfile::mailCheck(QString tName, QString tMail)
{
    if(!userExist(tName))
    {
        return false;
    }
    bool tResult=(INIActivated->getValue(tName,"Mail")==tMail);
    return tResult;
}
