#ifndef PASSWORDMANAGE_H
#define PASSWORDMANAGE_H

#include <QString>
#include "iniservice.h"
#include <QFile>
#include <QIODevice>

class PasswordManage
{
public:
    PasswordManage(QString tcurrentUser);

    INIService *INIPWManage;

    //读取所有密码
    void readAllLabel();

    //读取选中的密码的具体内容
    void readSelectedLabel(QString tlabel);

    //编辑选中的密码
    void editSelectedLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers);

    //删除选中的密码
    void deleSelectedLabel(QString tlabel);

    //添加密码
    void addNewLabel(QString tlabel,QString tname,QString tpassword,QString ttarget,QString tothers);

    //导出所有密码
    bool outputAllInfo(QString filePath);

    //获取所有密码
    QStringList getAllLabel();

    //获取选中的密码的具体内容
    QString getNowLabel();
    QString getNowName();
    QString getNowPassword();
    QString getNowTarget();
    QString getNowOthers();

    //获取一个随机字符串（随机密码）
    QString getRandomPW(int minLength,int maxLength);

    //查询密码是否已存在
    bool labelExist(QString tlabel);

private:
    //当前用户
    QString currentUser;

    //密码配置文件路径
    QString passwordINIPath;

    //保存所有密码的标签
    QStringList listOfAllLabel;

    //当前密码的具体内容
    QString nowLabel;
    QString nowName;
    QString nowPassword;
    QString nowTarget;
    QString nowOthers;
};

#endif // PASSWORDMANAGE_H
